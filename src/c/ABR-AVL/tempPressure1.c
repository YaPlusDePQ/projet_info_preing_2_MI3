#include "../mainDefine.h"

/* -------------------------------------------- init and kill functions --------------------------------------------*/

stationNode* newStationNode(int station, float value){
    stationNode* newNode = malloc(sizeof(stationNode));
    if(newNode==NULL) ERR(4, "newStationNode memory allocation failed.\n");
    newNode->station = station;
    newNode->min = value;
    newNode->max = value;
    newNode->avg = value;
    newNode->avgc = 1;
    newNode->lc = NULL;
    newNode->rc = NULL;
    DPRINTF("[newStationNode] [%d]: min:%f, max:%f, avg:%f, avgc:%d", newNode->station, newNode->min, newNode->max, newNode->avg, newNode->avgc);
    return newNode;
}

void freeStationNodeTree(stationNode* head){
    if(head->lc != NULL) freeStationNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeStationNodeTree(head->rc); //free all right child
    DPRINTF("[freeStationNodeTree] freeing %p ", head);
    if(head != NULL){
        free(head);
        DPRINTF("[DONE]\n");
    }
    else{
        DPRINTF("[FAILED]\n");
        ERR(101, "Impossible value for head imply memory leak or losing track of head during process.");
    }
}


int SizeOfStationNodeTree(stationNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfStationNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfStationNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

int setHeightStationNode(stationNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightStationNode(head->lc);
        int hrc = setHeightStationNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1;
    }
}

stationNode* RightRotationStationNodeTree(stationNode* unstablehead){
    stationNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

stationNode* LeftRotationStationNodeTree(stationNode* unstablehead){
    stationNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

stationNode* DRightRotationStationNodeTree(stationNode* unstablehead){
    unstablehead->rc = LeftRotationStationNodeTree(unstablehead->rc);
    return RightRotationStationNodeTree(unstablehead); 
}

stationNode* DLeftRotationStationNodeTree(stationNode* unstablehead){
    unstablehead->lc = RightRotationStationNodeTree(unstablehead->lc);
    return LeftRotationStationNodeTree(unstablehead);
}

int isUnbalancedStationNodeTree(stationNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedStationNodeTree(head->lc) || isUnbalancedStationNodeTree(head->rc);
}

stationNode* BalanceStationNodeTree(stationNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1 || (head->hl - head->hr) > 1){
        if((head->hl - head->hr) < -1){
            
            if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationStationNodeTree(head);
            else head = RightRotationStationNodeTree(head);
        }
        else{
            if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationStationNodeTree(head);
            else head = LeftRotationStationNodeTree(head);
        }

        return head;
    }
    head->lc = BalanceStationNodeTree(head->lc);
    head->rc = BalanceStationNodeTree(head->rc);

    return head;
}

/* -------------------------------------------- sorting functions --------------------------------------------*/

stationNode* compileStationData(stationNode* head, int station, float value){
    if(head == NULL) return newStationNode(station, value);
    
    if(head->station == station) {
        DPRINTF("[compileStationData] updating existing node ");
        head->min = value < head->min ? value : head->min; 
        head->max = value > head->max ? value : head->max; 
        head->avg += value;
        head->avgc++;
        return head;
    }

    if(station <= head->station){
        if(head->lc != NULL) compileStationData(head->lc, station, value);
        else head->lc = newStationNode(station, value);
    }
    else{
        if(head->rc != NULL) compileStationData(head->rc, station, value);
        else head->rc = newStationNode(station, value);
    }

    return head;
}

void _writeInFileDescendingTP1(FILE* file, stationNode* current){
    if(current->rc != NULL) _writeInFileDescendingTP1(file, current->rc);
    if(fprintf(file, "%d;%f;%f;%f\n", current->station, current->min, current->max, current->avg/current->avgc) < 0) ERR(1, "Can't write data in file\n");  // @EDIT FOR ORDER
    if(current->lc != NULL) _writeInFileDescendingTP1(file, current->lc);
}
/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
// */
void _writeInFileAscendingTP1(FILE* file, stationNode* current){
    if(current->lc  != NULL) _writeInFileAscendingTP1(file, current->lc);
    if(fprintf(file, "%d;%f;%f;%f\n", current->station, current->min, current->max, current->avg/current->avgc) < 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->rc != NULL) _writeInFileAscendingTP1(file, current->rc);
}

int TempPressureMode1ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(120, "Failed to open file '%s'", sourcePath);

    int info = 0;
    stationNode *stationTree = NULL;
    float value = 0;
    int station = 0;
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++; 
        value = 0;
        station = 0;
        int sscanfr = 0;

        sscanfr=sscanf(line,"%d;%f",&station, &value); // @EDIT FOR ORDER
        if (sscanfr==2) stationTree = compileStationData(stationTree, station, value);
        ERR(1, "Can't read data in line %d.\n", info);
        printf("\r[TempPressureMode1ABRAVL] Compiling data %d/?     ", info);

        if(avl){
            printf("Balancing tree...");
            setHeightStationNode(stationTree);
            while(isUnbalancedStationNodeTree(stationTree)){
                stationTree = BalanceStationNodeTree(stationTree);
                setHeightStationNode(stationTree);
                
            }
        }
    }
    printf("\r[TempPressureMode1ABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, SizeOfStationNodeTree(stationTree, 0));

    printf("[TempPressureMode1ABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) ERR(120, "Failed to create file '%s'", outPath);

    printf("[TempPressureMode1ABRAVL] seting up first line\n");
    char st[20] = "";
    char v[20]= "";
    rewind(source);
    fscanf(source, "%[^;\n];%[^;\n]", st, v);
    fprintf(out, "%s;%s min; %s max; %s moyenne\n",st, v, v, v); // @EDIT FOR ORDER

    printf("[TempPressureMode1ABRAVL] writting data\n");
    if(descending) _writeInFileDescendingTP1(out, stationTree);
    else _writeInFileAscendingTP1(out, stationTree);
    
    printf("[TempPressureMode1ABRAVL] cleaning up\n");
    freeStationNodeTree(stationTree);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode1ABRAVL] DONE\n");
    return 0;
}
