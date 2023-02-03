#include "../mainDefine.h"

/* -------------------------------------------- StationNode strcuture dependency -------------------------------------------- */

/**
*  \brief Create new dateNode element.
*
*  \param date Date in the file.
*  \param dateint date in hours.
*  \param station Station id.
*  \param value Temperature or pression of the station.
*
*  \return Pointer to the new element.
*/
dateNode* newDateNode(const char* date, long long int dateint, int station, float value){
    dateNode* newNode  =  malloc(sizeof(dateNode));
    if(newNode==NULL) exit(120);
    strcpy(newNode->datestr, date);
    newNode->dateint = dateint;
    newNode->stationTree = newStationNode(station, value);
    newNode->lc = NULL;
    newNode->rc = NULL;
    return newNode;
}

/**
*  \brief Free dateNode tree dynamics allocations.
*  
*  \param head Head of the tree.
*/
void freeDateNodeTree(dateNode* head){
    if(head->lc != NULL) freeDateNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeDateNodeTree(head->rc); //free all right child
    if(head != NULL){
        freeStationNodeTree(head->stationTree); //free stationNode inner tree
        free(head);
    }
    else{
        exit(121);
    }
}

/**
*  \brief Give number of node of a dateNode tree.
*  
*  \param head Head of the tree.
*
*  \return Number of node(s).
*/
int SizeOfDateNodeTree(dateNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfDateNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfDateNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

/**
*  \brief Set height of each node of a dateNode tree.
*  
*  \param head Head of the tree.
*
*  \return Height of the tree.
*/
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

/**
*  \brief Right rotation balancing of a dateNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
dateNode* RightRotationDateNodeTree(dateNode* unstablehead){
    dateNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

/**
*  \brief Left rotation balancing of a dateNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
dateNode* LeftRotationDateNodeTree(dateNode* unstablehead){
    dateNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

/**
*  \brief "Double right" rotation balancing of a dateNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
dateNode* DRightRotationDateNodeTree(dateNode* unstablehead){
    unstablehead->rc = LeftRotationDateNodeTree(unstablehead->rc);
    return RightRotationDateNodeTree(unstablehead); 
}

/**
*  \brief "Double left" rotation balancing of a dateNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
dateNode* DLeftRotationDateNodeTree(dateNode* unstablehead){
    unstablehead->lc = RightRotationDateNodeTree(unstablehead->lc);
    return LeftRotationDateNodeTree(unstablehead);
}

/**
*  \brief Test if a dateNode tree need balancing.
*  
*  \param head Head of the tree.
*
*  \return 0 if balanced, 1 otherwise.
*/
int isUnbalancedDateNodeTree(dateNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedDateNodeTree(head->lc) || isUnbalancedDateNodeTree(head->rc);
}

/**
*  \brief Balanced a dateNode tree 1 time.
*  
*  \param head Head of the tree.
*
*  \return New HMNode tree's head.
*/
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

/**
*  \brief Add new dateNode only if the date isn't in the tree, if it is in, update the value if mode 2
* and add the station to the corresponding dateNode stationNode tree if mode 3.
*  
*  \param date Date in the file.
*  \param dateint date in hours.
*  \param station Station id.
*  \param value Temperature or pression of the station.
*
*  \return New dateNode tree's head.
*/
dateNode* compileDateData_ABRAVL(int mode, dateNode* head, const char* date, long long int dateint, int station, float value){
    if(head == NULL) return newDateNode(date, dateint, station, value);
    
    if(head->dateint == dateint){
        switch(mode){
            case 2:
                head->stationTree->avg += value;
                head->stationTree->avgc++;
                break;
            case 3:
                head->stationTree = compileStationData_ABRAVL(head->stationTree, station, value); //add the station to the tree
                break;
        }
        return head;
    }

    if(dateint <= head->dateint){
        if(head->lc != NULL) compileDateData_ABRAVL(mode, head->lc, date, dateint, station, value);
        else head->lc = newDateNode(date, dateint, station, value);
    }
    else{
        if(head->rc != NULL) compileDateData_ABRAVL(mode, head->rc, date, dateint, station, value);
        else head->rc = newDateNode(date, dateint, station, value);
    }

    return head;
}

/**
*  \brief Recursive call for writing in a Ascending order stationNode tree values in t3/p3 format.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileStationTreeTP23_ABRAVL(FILE* file, const char* date, stationNode* current){
    if(current->lc != NULL) writeInFileStationTreeTP23_ABRAVL(file, date, current->lc);
    if(fprintf(file, "%s;%d;%f\n", date, current->station, current->avg/current->avgc)< 0) exit(320);//ERR(1, "Can't write data in file\n"); // @EDIT FOR ORDER
    if(current->rc != NULL) writeInFileStationTreeTP23_ABRAVL(file, date, current->rc);

}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileDescendingTP23_ABRAVL(FILE* file, int mode, dateNode* current){
    if(current->rc != NULL) writeInFileDescendingTP23_ABRAVL(file, mode, current->rc);
    switch(mode){
        case 2:
            if(fprintf(file, "%s;%f\n", current->datestr, current->stationTree->avg/current->stationTree->avgc)< 0) exit(321); // @EDIT FOR ORDER
            break;
        case 3:
            writeInFileStationTreeTP23_ABRAVL(file, current->datestr, current->stationTree);
            fputs("\n\n", file);
            break;
    }
    if(current->lc != NULL) writeInFileDescendingTP23_ABRAVL(file, mode, current->lc);
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileAscendingTP23_ABRAVL(FILE* file, int mode, dateNode* current){
    if(current->lc != NULL) writeInFileAscendingTP23_ABRAVL(file, mode, current->lc);
    switch(mode){
        case 2:
            if(fprintf(file, "%s;%f\n", current->datestr, current->stationTree->avg/current->stationTree->avgc)< 0) exit(322); // @EDIT FOR ORDER
            break;
        case 3:
            writeInFileStationTreeTP23_ABRAVL(file, current->datestr, current->stationTree);
            fputs("\n\n", file);
            break;
    }
    if(current->rc != NULL) writeInFileAscendingTP23_ABRAVL(file, mode, current->rc);
}


/**
*  \brief Sort a file for t2-3 and p2-3 mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param avl 0 for ABR sorting, 1 for AVL sorting.
*  \param mode 2 for -t2/p2 sorting, 3 for -t3/p3 sorting.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int TempPressureMode23_ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(122);

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
        int sscanfr=0; //make sur that the datas are correctly collected
        strcpy(date, "");

        switch(mode){
            case 2:
                sscanfr=sscanf(line,"%[^;];%f", date, &value); // @EDIT FOR ORDER
                station = 0;
                break;
            case 3:
                sscanfr=sscanf(line,"%d;%[^;];%f",&station, date, &value); // @EDIT FOR ORDER
                break;

        }
        switch(sscanfr){
            case 0:
                exit(220);
                break;
            case 2:
                if(mode==2) dateTree = compileDateData_ABRAVL(mode, dateTree, date, dateToInt(date), station, value);
                break;
            case 3:
                if(mode==3) dateTree = compileDateData_ABRAVL(mode, dateTree, date, dateToInt(date), station, value);
                break;
        }
       
        printf("\r[TempPressureMode23_ABRAVL] Compiling data %d/?     ", info);

        if(avl){
            printf("Balancing tree...");
            setHeightDateNode(dateTree);
            while(isUnbalancedDateNodeTree(dateTree)){
                dateTree = BalanceDateNodeTree(dateTree);
                setHeightDateNode(dateTree);
                
            }
        }
    }
    printf("\r[TempPressureMode23_ABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, SizeOfDateNodeTree(dateTree, 0));

    printf("[TempPressureMode23_ABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(123);

    printf("[TempPressureMode23_ABRAVL] seting up first line\n");
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
    
    printf("[TempPressureMode23_ABRAVL] writting data\n");
    if(descending) writeInFileDescendingTP23_ABRAVL(out, mode, dateTree);
    else writeInFileAscendingTP23_ABRAVL(out, mode, dateTree);
    
    printf("[TempPressureMode23_ABRAVL] cleaning up\n");
    freeDateNodeTree(dateTree);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode23_ABRAVL] DONE\n");
    return 0;
}

/**
*  \brief Sort a file for -t and -p mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param avl 0 for ABR sorting, 1 for AVL sorting.
*  \param mode 1,2 or 3.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int TempPressureMode_ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending){
    if(mode==1) TempPressureMode1_ABRAVL(sourcePath, outPath, avl, descending);
    else TempPressureMode23_ABRAVL(sourcePath, outPath, avl, mode, descending);
    return 0;
}
