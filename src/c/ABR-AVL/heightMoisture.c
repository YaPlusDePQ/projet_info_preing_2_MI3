#include "../mainDefine.h"

/* -------------------------------------------- init and kill functions --------------------------------------------*/
/**
*  \brief create new HMNode element.
*
*  \param station station id.
*  \param value height or moisture of station.
*
*  \return pointer to the new node.
*/
HMNode* newHMNode(int station, int value, const char* coord){
    HMNode* newNode = malloc(sizeof(HMNode));
    if(newNode==NULL) ERR(4, "newHMNode memory allocation failed.\n");
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->station = station;
    newNode->value = value;
    strcpy(newNode->coord, coord);
    DPRINTF("[newHMNode] [%d]: %d %s\n",newNode->station, newNode->value, newNode->coord);
    return newNode;
}

/**
*  \brief free HMNode tree.
*  
*  \param head head of the tree.
*/
void freeHMNodeTree(HMNode* head){
    if(head->lc != NULL) freeHMNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeHMNodeTree(head->rc); //free all right child
    DPRINTF("[freeHMNodeTree] freeing %p ", head);
    if(head != NULL){
        free(head);
        DPRINTF("[DONE]\n");
    }
    else{
        DPRINTF("[FAILED]\n");
        ERR(101, "Impossible value for head imply memory leak or losing track of head during process.");
    }
}

int SizeOfHMNodeTree(HMNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfHMNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfHMNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

int setHeightHMNode(HMNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightHMNode(head->lc);
        int hrc = setHeightHMNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1;
    }
}

HMNode* RightRotationHMNodeTree(HMNode* unstablehead){
    HMNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

HMNode* LeftRotationHMNodeTree(HMNode* unstablehead){
    HMNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

HMNode* DRightRotationHMNodeTree(HMNode* unstablehead){
    unstablehead->rc = LeftRotationHMNodeTree(unstablehead->rc);
    return RightRotationHMNodeTree(unstablehead); 
}

HMNode* DLeftRotationHMNodeTree(HMNode* unstablehead){
    unstablehead->lc = RightRotationHMNodeTree(unstablehead->lc);
    return LeftRotationHMNodeTree(unstablehead);
}

int isUnbalancedHMNodeTree(HMNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedHMNodeTree(head->lc) || isUnbalancedHMNodeTree(head->rc);
}

HMNode* BalanceHMNodeTree(HMNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1 || (head->hl - head->hr) > 1){
        if((head->hl - head->hr) < -1){
            
            if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationHMNodeTree(head);
            else head = RightRotationHMNodeTree(head);
        }
        else{
            if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationHMNodeTree(head);
            else head = LeftRotationHMNodeTree(head);
        }

        return head;
    }
    head->lc = BalanceHMNodeTree(head->lc);
    head->rc = BalanceHMNodeTree(head->rc);

    return head;
}


/* -------------------------------------------- sorting functions --------------------------------------------*/

/**
*  \brief add new HMNode only if the station isn't in the tree, if it is in, take the higher value.
*  
*  \param head head of the tree.
*  \param station station id.
*  \param value height or moisture of station.
*
*  \return new head pf the tree.
*/
HMNode* compileHMData(HMNode* head, int station, int value, const char* coord){
    if(head == NULL) return newHMNode(station, value, coord);
    
    if(head->station == station){
        DPRINTF("[compileHMData] updating existing node ");
        head->value = value > head->value ? value : head->value; 
        if( !strcmp(head->coord, "")) strcpy(head->coord, coord);
        return head;
    }

    if(station <= head->station){
        if(head->lc != NULL) compileHMData(head->lc, station, value, coord);
        else head->lc = newHMNode(station, value, coord);
    }
    else{
        if(head->rc != NULL) compileHMData(head->rc, station, value, coord);
        else head->rc = newHMNode(station, value, coord);
    }

    return head;
}

/**
*  \brief add a HMNode element in the tree by his height.
*  
*  \param head head of the tree.
*  \param toSort element to add.
*
*  \return new head pf the tree.
*/
HMNode* _sortHMData(HMNode* head, HMNode* toSort){

    if(head == NULL) { return newHMNode(toSort->station, toSort->value, toSort->coord);}

    if(toSort->value <= head->value){
        if(head->lc != NULL) _sortHMData(head->lc, toSort);
        else head->lc = newHMNode(toSort->station, toSort->value, toSort->coord);;
    }
    else{
        if(head->rc != NULL) _sortHMData(head->rc, toSort);
        else head->rc = newHMNode(toSort->station, toSort->value, toSort->coord);;
    }
    
    return head;
}

/**
*  \brief copy and sort a HMNode tree by his height.
*  
*  \param head head of the tree to sort and copy.
*  \param sortedHead new tree head's.
*
*  \return new tree head's.
*/
HMNode* sortHMNodeTree(HMNode* head, HMNode* sortedHead){
    sortedHead = _sortHMData(sortedHead, head);
    if(head->lc != NULL) sortHMNodeTree(head->lc, sortedHead);
    if(head->rc != NULL) sortHMNodeTree(head->rc, sortedHead);
    return sortedHead;
}

void _writeInFileDescendingHM(FILE* file, HMNode* current){
    if(current->rc != NULL) _writeInFileDescendingHM(file, current->rc);
    if(fprintf(file, "%d;%d;%s\n", current->station, current->value, current->coord) < 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->lc != NULL) _writeInFileDescendingHM(file, current->lc);
}
/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
// */
void _writeInFileAscendingHM(FILE* file, HMNode* current){
    if(current->lc != NULL) _writeInFileAscendingHM(file, current->lc);
    if(fprintf(file, "%d;%d;%s\n", current->station, current->value, current->coord) < 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->rc != NULL) _writeInFileAscendingHM(file, current->rc);
}


/**
 *  \brief print tree.
 *
 *  \param dt Type of data stored in the node.
 *  \param head tree to print.
 */
int HeightMoistureModeABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(120, "Failed to create file '%s'", sourcePath);

    int info = 0;
    HMNode *HMTree = NULL;
    int value = 0;
    int station = 0;
    char coord[30] = "";
    float x=0;
    float y=0;
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++;
        value = 0;
        station = 0;
        strcpy(coord, "");
        
        switch(mode){
            case HEIGHTMODE: //height
                if(sscanf(line,"%d;%f;%f;%d",&station, &x, &y, &value) == 0) ERR(1, "Can't read data in line %d.\n", info);// @EDIT FOR ORDER
                break;
            case MOISTUREMODE: //moisture
                if(sscanf(line,"%d;%d;%f;%f",&station, &value, &x, &y) == 0) ERR(1, "Can't read data in line %d.\n", info);// @EDIT FOR ORDER
                break;
        }
        
        sprintf(coord, "%f;%f", x,y);
        HMTree = compileHMData(HMTree, station, value, coord);
        printf("\r[HeightMoistureModeABRAVL] Compiling data %d/?     ", info);

        if(avl){
            printf("Balancing tree...");
            setHeightHMNode(HMTree);
            while(isUnbalancedHMNodeTree(HMTree)){
                HMTree = BalanceHMNodeTree(HMTree);
                setHeightHMNode(HMTree);
            }
        }

    }
    printf("\r[HeightMoistureModeABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, SizeOfHMNodeTree(HMTree, 0));

    printf("[HeightMoistureModeABRAVL] sorting tree\n");
    HMNode* sortedHMTree = sortHMNodeTree(HMTree, NULL);
    printf("[sortHMNodeTree] cleaning up old tree\n");
    freeHMNodeTree(HMTree);
    
    printf("[HeightMoistureModeABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) ERR(120, "Failed to create file '%s'", outPath);
    
    printf("[HeightMoistureModeABRAVL] seting up first line\n");
    char c0[20] = "";
    char c1[20]= "";
    char c2[20]="";
    char c3[20]="";
    rewind(source);
    fscanf(source, "%[^;\n];%[^;\n];%[^;\n];%[^;\n]", c0, c1, c2, c3);
    switch(mode){
        case HEIGHTMODE:
            fprintf(out, "%s;%s max;%s;%s\n", c0,c3,c1,c2);
            break;
        case MOISTUREMODE:
            fprintf(out, "%s;%s max;%s;%s\n", c0,c1,c2,c3);
            break;  
    }
    

    printf("[HeightMoistureModeABRAVL] writting data\n");
    if(descending) _writeInFileDescendingHM(out, sortedHMTree);
    else _writeInFileAscendingHM(out, sortedHMTree);
    
    printf("[HeightMoistureModeABRAVL] cleaning up\n");
    freeHMNodeTree(sortedHMTree);
    fclose(source);
    fclose(out);
    printf("[HeightMoistureModeABRAVL] DONE\n");
    return 0;
}