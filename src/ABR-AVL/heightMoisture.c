#include "../mainDefine.h"

/* -------------------------------------------- HMNode strcuture dependency -------------------------------------------- */

/**
*  \brief Create new HMNode element.
*
*  \param station Station id.
*  \param value Height or moisture of the station.
*  \param coord Coordinate of the station.
*
*  \return Pointer to the new element.
*/
HMNode* newHMNode(int station, int value, const char* coord){
    HMNode* newNode = malloc(sizeof(HMNode));
    if(newNode==NULL) exit(100);
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->station = station;
    newNode->value = value;
    strcpy(newNode->coord, coord);
    return newNode;
}

/**
*  \brief Free HMNode tree dynamics allocations.
*  
*  \param head Head of the tree.
*/
void freeHMNodeTree(HMNode* head){
    if(head->lc != NULL) freeHMNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeHMNodeTree(head->rc); //free all right child
    if(head != NULL){
        free(head);
    }
    else{
        exit(101);
    }
}

/**
*  \brief Give number of node of a HMNode tree.
*  
*  \param head Head of the tree.
*
*  \return Number of node(s).
*/
int SizeOfHMNodeTree(HMNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfHMNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfHMNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

/**
*  \brief Set height of each node of a HMNode tree.
*  
*  \param head Head of the tree.
*
*  \return Height of the tree.
*/
int setHeightHMNode(HMNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightHMNode(head->lc);
        int hrc = setHeightHMNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1; //return max height of each sub tree+1
    }
}

/**
*  \brief Right rotation balancing of a HMNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
HMNode* RightRotationHMNodeTree(HMNode* unstableNode){
    HMNode* BalancedNode = unstableNode->rc;
    unstableNode->rc = BalancedNode->lc;
    BalancedNode->lc = unstableNode;
    return BalancedNode;
}

/**
*  \brief Left rotation balancing of a HMNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
HMNode* LeftRotationHMNodeTree(HMNode* unstableNode){
    HMNode* BalancedNode = unstableNode->lc;
    unstableNode->lc = BalancedNode->rc;
    BalancedNode->rc = unstableNode;
    return BalancedNode;
}

/**
*  \brief "Double right" rotation balancing of a HMNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
HMNode* DRightRotationHMNodeTree(HMNode* unstableNode){
    unstableNode->rc = LeftRotationHMNodeTree(unstableNode->rc);
    return RightRotationHMNodeTree(unstableNode); 
}

/**
*  \brief "Double left" rotation balancing of a HMNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
HMNode* DLeftRotationHMNodeTree(HMNode* unstableNode){
    unstableNode->lc = RightRotationHMNodeTree(unstableNode->lc);
    return LeftRotationHMNodeTree(unstableNode);
}

/**
*  \brief Test if a HMNode tree need balancing.
*  
*  \param head Head of the tree.
*
*  \return 0 if balanced, 1 otherwise.
*/
int isUnbalancedHMNodeTree(HMNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedHMNodeTree(head->lc) || isUnbalancedHMNodeTree(head->rc);
}

/**
*  \brief Balanced a HMNode tree 1 time.
*  
*  \param head Head of the tree.
*
*  \return New HMNode tree's head.
*/
HMNode* BalanceHMNodeTree(HMNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1){
        if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationHMNodeTree(head);
        else head = RightRotationHMNodeTree(head);
        return head;
    }
    else if((head->hl - head->hr) > 1){
        if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationHMNodeTree(head);
        else head = LeftRotationHMNodeTree(head);
        return head;
    }
        
    head->lc = BalanceHMNodeTree(head->lc);
    head->rc = BalanceHMNodeTree(head->rc);

    return head;
}

/* -------------------------------------------- Sorting functions --------------------------------------------*/

/**
*  \brief Add new HMNode only if the station isn't in the tree, if it is in, take the higher value.
*  
*  \param head Head of the tree.
*  \param station Station id.
*  \param value Height or moisture of station.
*  \param coord Coordinate of the station.
*
*  \return New HMNode tree's head.
*/
HMNode* compileHMData_ABRAVL(HMNode* head, int station, int value, const char* coord){
    if(head == NULL) return newHMNode(station, value, coord); //if the tree doesnt exist (only 1 time)
    
    if(head->station == station){ //update already existing station
        head->value = value > head->value ? value : head->value; 
        if( !strcmp(head->coord, "")) strcpy(head->coord, coord);
        return head;
    }

    if(station <= head->station){ 
        if(head->lc != NULL) compileHMData_ABRAVL(head->lc, station, value, coord); //go in deep in not at a leaf
        else head->lc = newHMNode(station, value, coord);
    }
    else{
        if(head->rc != NULL) compileHMData_ABRAVL(head->rc, station, value, coord); //go in deep in not at a leaf
        else head->rc = newHMNode(station, value, coord);
    }

    return head;
}

/**
*  \brief Add a HMNode element in the tree by his height/moisture.
*  
*  \param head Head of the tree.
*  \param toSort Element to add.
*
*  \return New HMNode tree's head.
*/
HMNode* _sortHMData_ABRAVL(HMNode* head, HMNode* toSort){

    if(head == NULL) { return newHMNode(toSort->station, toSort->value, toSort->coord);} //if the tree doesnt exist (only 1 time)

    if(toSort->value <= head->value){
        if(head->lc != NULL) _sortHMData_ABRAVL(head->lc, toSort); //go in deep in not at a leaf
        else head->lc = newHMNode(toSort->station, toSort->value, toSort->coord);;
    }
    else{
        if(head->rc != NULL) _sortHMData_ABRAVL(head->rc, toSort); //go in deep in not at a leaf
        else head->rc = newHMNode(toSort->station, toSort->value, toSort->coord);;
    }
    
    return head;
}

/**
*  \brief copy and sort a HMNode tree by his height/moisture.
*  
*  \param head Head of the tree to sort and copy.
*  \param sortedHead New HMNode tree's head. (should always be NULL)
*
*  \return New HMNode tree's head.
*/
HMNode* sortHMNodeTree(HMNode* head, HMNode* sortedHead){
    sortedHead = _sortHMData_ABRAVL(sortedHead, head);
    if(head->lc != NULL) sortHMNodeTree(head->lc, sortedHead);
    if(head->rc != NULL) sortHMNodeTree(head->rc, sortedHead);
    return sortedHead;
}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileDescendingHM_ABRAVL(FILE* file, HMNode* current){
    if(current->rc != NULL) writeInFileDescendingHM_ABRAVL(file, current->rc);
    if(fprintf(file, "%d;%d;%s\n", current->station, current->value, current->coord) < 0) exit(300); // @EDIT FOR ORDER
    if(current->lc != NULL) writeInFileDescendingHM_ABRAVL(file, current->lc);
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileAscendingHM_ABRAVL(FILE* file, HMNode* current){
    if(current->lc != NULL) writeInFileAscendingHM_ABRAVL(file, current->lc);
    if(fprintf(file, "%d;%d;%s\n", current->station, current->value, current->coord) < 0) exit(300); // @EDIT FOR ORDER
    if(current->rc != NULL) writeInFileAscendingHM_ABRAVL(file, current->rc);
}


/**
*  \brief Sort a file for -m or -h mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param avl 0 for ABR sorting, 1 for AVL sorting.
*  \param mode HEIGHTMODE for -h, MOISTUREMODE for -m.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int HeightMoistureMode_ABRAVL(const char* sourcePath, const char* outPath, int mode, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(102);

    int info = 0; //debug info
    HMNode *HMTree = NULL;
    int value = 0;
    int station = 0;
    char coord[30] = "";
    float x=0; //x coordinate buffer
    float y=0; //y coordinate buffer
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //read the line + test for EOF
        info++; //update debug
        value = 0;
        station = 0;
        int sscanfr = 0; //make sur that the datas are correctly collected
        strcpy(coord, "");
        
        switch(mode){
            case HEIGHTMODE: //height
                sscanfr = sscanf(line,"%d;%f;%f;%d",&station, &x, &y, &value);// @EDIT FOR ORDER
                break;
            case MOISTUREMODE: //moisture
                sscanfr = sscanf(line,"%d;%d;%f;%f",&station, &value, &x, &y);// @EDIT FOR ORDER
                break;
        }
        
        sprintf(coord, "%f;%f", x,y); //write x and y into coord
        if(sscanfr == 4) HMTree = compileHMData_ABRAVL(HMTree, station, value, coord); //add the new datas
        if(sscanfr == 0) exit(200);
        printf("\r[HeightMoistureMode_ABRAVL] Compiling data %d/?     ", info);

        if(avl){ //balance the tree if AVL mode
            printf("Balancing tree...");
            setHeightHMNode(HMTree); 
            while(isUnbalancedHMNodeTree(HMTree)){ //do rotation while the tree is unbalance
                HMTree = BalanceHMNodeTree(HMTree);
                setHeightHMNode(HMTree);
            }
        }

    }
    printf("\r[HeightMoistureMode_ABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, SizeOfHMNodeTree(HMTree, 0));

    printf("[HeightMoistureMode_ABRAVL] Sorting tree\n");
    HMNode* sortedHMTree = sortHMNodeTree(HMTree, NULL); //sort the tree by value

    printf("[HeightMoistureMode_ABRAVL] Cleaning up old tree\n");
    freeHMNodeTree(HMTree);
    
    printf("[HeightMoistureMode_ABRAVL] Creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(103);
    
    printf("[HeightMoistureMode_ABRAVL] Writting column\n"); //organise column name
    char c0[20] = "";
    char c1[20]= "";
    char c2[20]="";
    char c3[20]="";
    rewind(source);
    fscanf(source, "%[^;\n];%[^;\n];%[^;\n];%[^;\n]", c0, c1, c2, c3);
    switch(mode){ //make sure that column are in the same order as the data
        case HEIGHTMODE:
            fprintf(out, "%s;%s max;%s;%s\n", c0,c3,c1,c2);
            break;
        case MOISTUREMODE:
            fprintf(out, "%s;%s max;%s;%s\n", c0,c1,c2,c3);
            break;  
    }
    
    printf("[HeightMoistureMode_ABRAVL] Writting data\n"); //write data in output file
    if(descending) writeInFileDescendingHM_ABRAVL(out, sortedHMTree);
    else writeInFileAscendingHM_ABRAVL(out, sortedHMTree);
    
    printf("[HeightMoistureMode_ABRAVL] Cleaning up\n"); //free ressources
    freeHMNodeTree(sortedHMTree);
    fclose(source);
    fclose(out);
    printf("[HeightMoistureMode_ABRAVL] DONE\n");
    return 0;
}
