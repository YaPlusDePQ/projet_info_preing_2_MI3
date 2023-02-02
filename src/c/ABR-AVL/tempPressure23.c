#include "../mainDefine.h"

/* -------------------------------------------- init and kill functions --------------------------------------------*/

dateNode* newDateNode(const char* date, long long int dateint, int station, float value){
    dateNode* newNode  =  malloc(sizeof(dateNode));
    if(newNode==NULL) ERR(4, "newDateNode memory allocation failed.\n");
    strcpy(newNode->datestr, date);
    newNode->dateint = dateint;
    newNode->stationTree = newStationNode(station, value);
    newNode->lc = NULL;
    newNode->rc = NULL;
    DPRINTF("[newStationNode] datestr:%s dateint:%I64d stationTree:%p", newNode->datestr, newNode->dateint, newNode->stationTree);
    return newNode;
}

void freeDateNodeTree(dateNode* head){
    if(head->lc != NULL) freeDateNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeDateNodeTree(head->rc); //free all right child
    DPRINTF("[freeDateNodeTree] freeing %p ", head);
    if(head != NULL){
        freeStationNodeTree(head->stationTree);
        free(head);
        DPRINTF("[DONE]\n");
    }
    else{
        DPRINTF("[FAILED]\n");
        ERR(101, "Impossible value for head imply memory leak or losing track of head during process.");
    }
}

int SizeOfDateNodeTree(dateNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfDateNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfDateNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

int setHeightDateNode(dateNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightDateNode(head->lc);
        int hrc = setHeightDateNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1;
    }
}

dateNode* RightRotationDateNodeTree(dateNode* unstablehead){
    dateNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

dateNode* LeftRotationDateNodeTree(dateNode* unstablehead){
    dateNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

dateNode* DRightRotationDateNodeTree(dateNode* unstablehead){
    unstablehead->rc = LeftRotationDateNodeTree(unstablehead->rc);
    return RightRotationDateNodeTree(unstablehead); 
}

dateNode* DLeftRotationDateNodeTree(dateNode* unstablehead){
    unstablehead->lc = RightRotationDateNodeTree(unstablehead->lc);
    return LeftRotationDateNodeTree(unstablehead);
}

int isUnbalancedDateNodeTree(dateNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedDateNodeTree(head->lc) || isUnbalancedDateNodeTree(head->rc);
}

dateNode* BalanceDateNodeTree(dateNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1 || (head->hl - head->hr) > 1){
        if((head->hl - head->hr) < -1){
            
            if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationDateNodeTree(head);
            else head = RightRotationDateNodeTree(head);
        }
        else{
            if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationDateNodeTree(head);
            else head = LeftRotationDateNodeTree(head);
        }

        return head;
    }
    head->lc = BalanceDateNodeTree(head->lc);
    head->rc = BalanceDateNodeTree(head->rc);

    return head;
}


/* -------------------------------------------- sorting functions --------------------------------------------*/

dateNode* compileDateData(int mode, dateNode* head, const char* date, long long int dateint, int station, float value){
    if(head == NULL) return newDateNode(date, dateint, station, value);
    
    if(head->dateint == dateint){
        DPRINTF("[compileDateData] updating existing node ");
        switch(mode){
            case 2:
                head->stationTree->avg += value;
                head->stationTree->avgc++;
                break;
            case 3:
                head->stationTree = compileStationData(head->stationTree, station, value);
                break;
        }
        return head;
    }

    if(dateint <= head->dateint){
        if(head->lc != NULL) compileDateData(mode, head->lc, date, dateint, station, value);
        else head->lc = newDateNode(date, dateint, station, value);
    }
    else{
        if(head->rc != NULL) compileDateData(mode, head->rc, date, dateint, station, value);
        else head->rc = newDateNode(date, dateint, station, value);
    }

    return head;
}

void _writeInFileStationTreeTP23(FILE* file, const char* date, stationNode* current){
    if(current->lc != NULL) _writeInFileStationTreeTP23(file, date, current->lc);
    if(fprintf(file, "%s;%d;%f\n", date, current->station, current->avg/current->avgc)< 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->rc != NULL) _writeInFileStationTreeTP23(file, date, current->rc);

}

void _writeInFileDescendingTP23(FILE* file, int mode, dateNode* current){
    if(current->rc != NULL) _writeInFileDescendingTP23(file, mode, current->rc);
    switch(mode){
        case 2:
            if(fprintf(file, "%s;%f\n", current->datestr, current->stationTree->avg/current->stationTree->avgc)< 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
            break;
        case 3:
            _writeInFileStationTreeTP23(file, current->datestr, current->stationTree);
            fputs("\n\n", file);
            break;
    }
    if(current->lc != NULL) _writeInFileDescendingTP23(file, mode, current->lc);
}

void _writeInFileAscendingTP23(FILE* file, int mode, dateNode* current){
    if(current->lc != NULL) _writeInFileAscendingTP23(file, mode, current->lc);
    switch(mode){
        case 2:
            if(fprintf(file, "%s;%f\n", current->datestr, current->stationTree->avg/current->stationTree->avgc)< 0) ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
            break;
        case 3:
            _writeInFileStationTreeTP23(file, current->datestr, current->stationTree);
            fputs("\n\n", file);
            break;
    }
    if(current->rc != NULL) _writeInFileAscendingTP23(file, mode, current->rc);
}

int TempPressureMode23ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(120, "Failed to open file '%s'", sourcePath);

    int info = 0;
    dateNode *dateTree = NULL;
    float value = 0;
    int station = 0;
    char date[30] = "";
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++;
        value = 0;
        station = 0;
        strcpy(date, "");

        switch(mode){
            case 2:
                if(sscanf(line,"%[^;];%f", date, &value) == 0) ERR(1, "Can't read data in line %d.\n", info); // @EDIT FOR ORDER
                station = 0;
                break;
            case 3:
                if(sscanf(line,"%d;%[^;];%f",&station, date, &value) == 0) ERR(1, "Can't read data in line %d.\n", info); // @EDIT FOR ORDER
                break;

        }
        
        dateTree = compileDateData(mode, dateTree, date, dateToInt(date), station, value);
        printf("\r[TempPressureMode23ABRAVL] Compiling data %d/?     ", info);

        if(avl){
            printf("Balancing tree...");
            setHeightDateNode(dateTree);
            while(isUnbalancedDateNodeTree(dateTree)){
                dateTree = BalanceDateNodeTree(dateTree);
                setHeightDateNode(dateTree);
                
            }
        }
    }
    printf("\r[TempPressureMode23ABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, SizeOfDateNodeTree(dateTree, 0));

    printf("[TempPressureMode23ABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) ERR(120, "Failed to create file '%s'", outPath);

    printf("[TempPressureMode23ABRAVL] seting up first line\n");
    char st[20] = "";
    char d[20] = "";
    char v[20]= "";
    rewind(source);

    switch(mode){
        case 2:
            fscanf(source, "%[^;\n];%[^;\n]", d, v);
            fprintf(out, "%s;%s moyenne\n", d, v);
            break;
        case 3:
            fscanf(source, "%[^;\n];%[^;\n];%[^;\n]", st, d, v);
            fprintf(out, "%s;%s;%s\n", d, st, v);
            break;
    }
    
    printf("[TempPressureMode23ABRAVL] writting data\n");
    if(descending) _writeInFileDescendingTP23(out, mode, dateTree);
    else _writeInFileAscendingTP23(out, mode, dateTree);
    
    printf("[TempPressureMode23ABRAVL] cleaning up\n");
    freeDateNodeTree(dateTree);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode23ABRAVL] DONE\n");
    return 0;
}

int TempPressureModeABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending){
    return mode == 1 ? TempPressureMode1ABRAVL(sourcePath, outPath, avl, descending) : TempPressureMode23ABRAVL(sourcePath, outPath, avl, mode, descending);
}