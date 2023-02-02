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
windNode* newWindNode(int station, float direction, float speed, const char* coord){
    windNode* newNode = malloc(sizeof(windNode));
    if(newNode==NULL) ERR(4, "newWindNode memory allocation failed.\n");
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->station = station;
    newNode->tDirection = direction;
    newNode->tSpeed = speed;
    newNode->avgc = 1;
    newNode->hl = 0;
    newNode->hr = 0;
    strcpy(newNode->coord, coord);
    DPRINTF("[newHMNode] [%d]: %f %f %s\n",newNode->station, newNode->tDirection, newNode->tSpeed, newNode->coord);
    return newNode;
}

/**
*  \brief free HMNode tree.
*  
*  \param head head of the tree.
*/
void freeWindNodeTree(windNode* head){
    if(head->lc != NULL) freeWindNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeWindNodeTree(head->rc); //free all right child
    DPRINTF("[freeWindNodeTree] freeing %p ", head);
    if(head != NULL){
        free(head);
        DPRINTF("[DONE]\n");
    }
    else{
        DPRINTF("[FAILED]\n");
        ERR(101, "Impossible value for head imply memory leak or losing track of head during process.");
    }
}

int SizeOfWindNodeTree(windNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfWindNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfWindNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

int setHeightWindNode(windNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightWindNode(head->lc);
        int hrc = setHeightWindNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1;
    }
}

windNode* RightRotationWindNodeTree(windNode* unstablehead){
    windNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

windNode* LeftRotationWindNodeTree(windNode* unstablehead){
    windNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

windNode* DRightRotationWindNodeTree(windNode* unstablehead){
    unstablehead->rc = LeftRotationWindNodeTree(unstablehead->rc);
    return RightRotationWindNodeTree(unstablehead); 
}

windNode* DLeftRotationWindNodeTree(windNode* unstablehead){
    unstablehead->lc = RightRotationWindNodeTree(unstablehead->lc);
    return LeftRotationWindNodeTree(unstablehead);
}

int isUnbalancedWindNodeTree(windNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedWindNodeTree(head->lc) || isUnbalancedWindNodeTree(head->rc);
}

windNode* BalanceWindNodeTree(windNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1 || (head->hl - head->hr) > 1){
        if((head->hl - head->hr) < -1){
            
            if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationWindNodeTree(head);
            else head = RightRotationWindNodeTree(head);
        }
        else{
            if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationWindNodeTree(head);
            else head = LeftRotationWindNodeTree(head);
        }

        return head;
    }
    head->lc = BalanceWindNodeTree(head->lc);
    head->rc = BalanceWindNodeTree(head->rc);

    return head;
}

/* -------------------------------------------- sorting functions --------------------------------------------*/

windNode* compileWindData(windNode* head, int station, float direction, float speed, const char* coord){
    if(head == NULL) return newWindNode(station, direction, speed, coord);
    
    if(head->station == station) {
        DPRINTF("[compileWindData] updating existing node ");
        head->tDirection += direction;
        head->tSpeed += speed; 
        head->avgc++;
        if( !strcmp(head->coord, "")) strcpy(head->coord, coord);
        return head;
    }

    if(station <= head->station){
        if(head->lc != NULL) compileWindData(head->lc, station, direction, speed, coord);
        else head->lc = newWindNode(station, direction, speed, coord);
    }
    else{
        if(head->rc != NULL) compileWindData(head->rc, station, direction, speed, coord);
        else head->rc = newWindNode(station, direction, speed, coord);
    }

    return head;
}

void _writeInFileDescendingW(FILE* file, windNode* current){
    if(current->rc != NULL) _writeInFileDescendingW(file, current->rc);
    if(fprintf(file, "%d;%f;%f;%s\n", current->station, current->tDirection/current->avgc, current->tSpeed/current->avgc, current->coord) < 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->lc != NULL) _writeInFileDescendingW(file, current->lc);
}

void _writeInFileAscendingW(FILE* file, windNode* current){
    if(current->lc != NULL) _writeInFileAscendingW(file, current->lc);
    if(fprintf(file, "%d;%f;%f;%s\n", current->station, current->tDirection/current->avgc, current->tSpeed/current->avgc, current->coord) < 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->rc != NULL) _writeInFileAscendingW(file, current->rc);
}

int WindModeABRAVL(const char* sourcePath, const char* outPath, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(120, "Failed to create file '%s'", sourcePath);

    int info = 0;
    windNode *windTree = NULL;
    int station = 0;
    float windDirection = 0;
    float windSpeed = 0;
    char coord[30] = "";
    char line[1000] = ""; //line buffer
    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++;
        station = 0;
        windDirection = 0;
        windSpeed = 0;
        strcpy(coord, "");
        
        if(sscanf(line,"%d;%f;%f;%[^\n]",&station, &windDirection, &windSpeed, coord) == 0) ERR(1, "Can't read data in line %d.\n", info);// @EDIT FOR ORDER
        windTree = compileWindData(windTree, station, windDirection, windSpeed, coord);
        printf("\r[WindModeABRAVL] Compiling data %d/?", info);

        if(avl){
            printf("Balancing tree...");
            setHeightWindNode(windTree);
            while(isUnbalancedWindNodeTree(windTree)){
                windTree = BalanceWindNodeTree(windTree);
                setHeightWindNode(windTree);
                
            }
        }
    }
    printf("\r[WindModeABRAVL] Compiling data DONE. %d datas in %d nodes                \n", info, SizeOfWindNodeTree(windTree, 0));

    printf("[WindModeABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) ERR(120, "Failed to create file '%s'", outPath);

    fputs("ID OMM station;Vecteur X; Vecteur Y;X;Y\n", out);

    printf("[WindModeABRAVL] writting data\n");
    if(descending) _writeInFileDescendingW(out, windTree);
    else _writeInFileAscendingW(out, windTree);
    
    printf("[WindModeABRAVL] cleaning up\n");
    freeWindNodeTree(windTree);
    fclose(source);
    fclose(out);
    printf("[WindModeABRAVL] DONE\n");
    return 0;
}