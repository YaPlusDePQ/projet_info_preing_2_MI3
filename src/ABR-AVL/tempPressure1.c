#include "../mainDefine.h"

/* -------------------------------------------- StationNode strcuture dependency -------------------------------------------- */

/**
*  \brief Create new StationNode element.
*
*  \param station Station id.
*  \param value Temperature or pression of the station.
*
*  \return Pointer to the new element.
*/
stationNode* newStationNode(int station, float value){
    stationNode* newNode = malloc(sizeof(stationNode));
    if(newNode==NULL) exit(110);
    newNode->station = station;
    newNode->min = value;
    newNode->max = value;
    newNode->avg = value;
    newNode->avgc = 1;
    newNode->lc = NULL;
    newNode->rc = NULL;
    return newNode;
}

/**
*  \brief Free StationNode tree dynamics allocations.
*  
*  \param head Head of the tree.
*/
void freeStationNodeTree(stationNode* head){
    if(head->lc != NULL) freeStationNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeStationNodeTree(head->rc); //free all right child
    if(head != NULL){
        free(head);
    }
    else{
        exit(111);
    }
}

/**
*  \brief Give number of node of a StationNode tree.
*  
*  \param head Head of the tree.
*
*  \return Number of node(s).
*/
int SizeOfStationNodeTree(stationNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfStationNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfStationNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

/**
*  \brief Set height of each node of a stationNode tree.
*  
*  \param head Head of the tree.
*
*  \return Height of the tree.
*/
int setHeightStationNode(stationNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightStationNode(head->lc);
        int hrc = setHeightStationNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1; //return max height of each sub tree+1
    }
}

/**
*  \brief Right rotation balancing of a stationNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
stationNode* RightRotationStationNodeTree(stationNode* unstablehead){
    stationNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

/**
*  \brief Left rotation balancing of a stationNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
stationNode* LeftRotationStationNodeTree(stationNode* unstablehead){
    stationNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

/**
*  \brief "Double right" rotation balancing of a stationNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
stationNode* DRightRotationStationNodeTree(stationNode* unstablehead){
    unstablehead->rc = LeftRotationStationNodeTree(unstablehead->rc);
    return RightRotationStationNodeTree(unstablehead); 
}

/**
*  \brief "Double left" rotation balancing of a stationNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
stationNode* DLeftRotationStationNodeTree(stationNode* unstablehead){
    unstablehead->lc = RightRotationStationNodeTree(unstablehead->lc);
    return LeftRotationStationNodeTree(unstablehead);
}

/**
*  \brief Test if a stationNode tree need balancing.
*  
*  \param head Head of the tree.
*
*  \return 0 if balanced, 1 otherwise.
*/
int isUnbalancedStationNodeTree(stationNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedStationNodeTree(head->lc) || isUnbalancedStationNodeTree(head->rc);
}

/**
*  \brief Balanced a stationNode tree 1 time.
*  
*  \param head Head of the tree.
*
*  \return New HMNode tree's head.
*/
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

/**
*  \brief Add new stationNode only if the station isn't in the tree, if it is in, update the values.
*  
*  \param head Head of the tree.
*  \param station Station id.
*  \param value Temperatur of pression of the station.
*
*  \return New stationNode tree's head.
*/
stationNode* compileStationData_ABRAVL(stationNode* head, int station, float value){
    if(head == NULL) return newStationNode(station, value); //if the tree doesnt exist (only 1 time)
    
    if(head->station == station) { //update already existing station
        head->min = value < head->min ? value : head->min; 
        head->max = value > head->max ? value : head->max; 
        head->avg += value;
        head->avgc++;
        return head;
    }

    if(station <= head->station){
        if(head->lc != NULL) compileStationData_ABRAVL(head->lc, station, value);
        else head->lc = newStationNode(station, value);
    }
    else{
        if(head->rc != NULL) compileStationData_ABRAVL(head->rc, station, value);
        else head->rc = newStationNode(station, value);
    }

    return head;
}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileDescendingTP1_ABRAVL(FILE* file, stationNode* current){
    if(current->rc != NULL) writeInFileDescendingTP1_ABRAVL(file, current->rc);
    if(fprintf(file, "%d;%f;%f;%f\n", current->station, current->min, current->max, current->avg/current->avgc) < 0) exit(310);// @EDIT FOR ORDER
    if(current->lc != NULL) writeInFileDescendingTP1_ABRAVL(file, current->lc);
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileAscendingTP1_ABRAVL(FILE* file, stationNode* current){
    if(current->lc  != NULL) writeInFileAscendingTP1_ABRAVL(file, current->lc);
    if(fprintf(file, "%d;%f;%f;%f\n", current->station, current->min, current->max, current->avg/current->avgc) < 0) exit(311);// @EDIT FOR ORDER
    if(current->rc != NULL) writeInFileAscendingTP1_ABRAVL(file, current->rc);
}

/**
*  \brief Sort a file for -t1 or -p1 mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param avl 0 for ABR sorting, 1 for AVL sorting.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int TempPressureMode1_ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(112); 

    int info = 0;//debug info
    stationNode *stationTree = NULL;
    float value = 0;
    int station = 0;
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line
    printf("ok\n");
    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++; 
        value = 0;
        station = 0;
        int sscanfr = 0; //make sur that the datas are correctly collected
        
        sscanfr=sscanf(line,"%d;%f",&station, &value); // @EDIT FOR ORDER
        if (sscanfr==2) stationTree = compileStationData_ABRAVL(stationTree, station, value); //add the new datas
        if (sscanfr==0) exit(210); 
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
    if(out == NULL) exit(113);

    printf("[TempPressureMode1ABRAVL] seting up first line\n");
    char st[20] = "";
    char v[20]= "";
    rewind(source);
    fscanf(source, "%[^;\n];%[^;\n]", st, v);
    fprintf(out, "%s;%s min; %s max; %s moyenne\n",st, v, v, v); // @EDIT FOR ORDER

    printf("[TempPressureMode1ABRAVL] writting data\n");
    if(descending) writeInFileDescendingTP1_ABRAVL(out, stationTree);
    else writeInFileAscendingTP1_ABRAVL(out, stationTree);
    
    printf("[TempPressureMode1ABRAVL] cleaning up\n"); //free ressources
    freeStationNodeTree(stationTree);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode1ABRAVL] DONE\n");
    return 0;
}
