#include "../mainDefine.h"

/* -------------------------------------------- HMelmt strcuture dependency -------------------------------------------- */

/**
*  \brief Create new HMelmt element.
*
*  \param station Station id.
*  \param value Height or moisture of the station.
*  \param coord Coordinate of the station.
*
*  \return Pointer to the new element.
*/
HMelmt* newHMelmt(int station, int value, const char* coord){
    HMelmt* newElmt = malloc(sizeof(HMelmt));
    if(newElmt==NULL) exit(140);
    newElmt->next = NULL;
    newElmt->before = NULL;
    newElmt->station = station;
    newElmt->value = value;
    strcpy(newElmt->coord, coord);
    return newElmt;
}

/**
*  \brief Free HMelmt tree dynamics allocations.
*  
*  \param head Head of the linked list.
*/
void freeHMelmtLinkedList(HMelmt* head){
    if(head->next != NULL){
        freeHMelmtLinkedList(head->next);
    }
    free(head);
}

/**
*  \brief Give number of node of a HMelmt linked list.
*  
*  \param head Head of the linked list.
*
*  \return Number of element.
*/
int getSizeOfHMelmt(HMelmt* head){
    int i=0;
    while(head!=NULL){
        i++;
        head = head->next;
    }
    return i;
}

/**
*  \brief Add new HMelmt only if the station isn't in the linked list, if it is in, take the higher value.
*  
*  \param head Head of the linked list.
*  \param station Station id.
*  \param value Height or moisture of station.
*  \param coord Coordinate of the station.
*
*  \return New HMelmt linked list's head.
*/
HMelmt* compileHMData_TAB(HMelmt* head, int station, int value, const char* coord){
   
    if(head == NULL) return newHMelmt(station, value, coord);
    
    if(head->station < station){ //change head
        HMelmt* newHead = newHMelmt(station, value, coord);
        newHead->next = head;
        head->before = newHead;
        return newHead;
    }

    HMelmt* bh = head;
    HMelmt* newElement = NULL;
    while(bh != NULL){
        if(bh->station == station){ //update already existing station
            bh->value = value > bh->value ? value : bh->value; 
            if( !strcmp(bh->coord, "")) strcpy(bh->coord, coord);
            return head;
        }

        if(bh->next == NULL){
            newElement = newHMelmt(station, value, coord); //add to the end
            bh->next = newElement;
            newElement->before = bh->next;
            return head;
        }
        else if(station > bh->next->station){ //swap value
            newElement = newHMelmt(station, value, coord);
            newElement->next = bh->next;
            bh->next->before = newElement;
            newElement->before = bh;
            bh->next = newElement;
            return head;
        }

        bh= bh->next;
    }

    return head;
}

/**
*  \brief copy and sort a HMelmt linked list by his height/moisture.
*  
*  \param head Head of the linked list to sort and copy.
*  \param sortedHead New HMNode linked list's head. (should always be NULL)
*
*  \return New HMNode linked list's head.
*/
HMelmt* sortHMelmt_TAB(HMelmt* head, HMelmt* sortedHead){
    sortedHead = newHMelmt(head->station, head->value, head->coord);
    HMelmt* bh = head;
    HMelmt* bsh = sortedHead;
    HMelmt* blmt = NULL;
    int info=1;
    int max=getSizeOfHMelmt(head);

    while(bh != NULL){
        blmt = NULL;
        bsh = sortedHead;
        printf("\r[sortHMelmt] %d/%d nodes sorted", info, max);

        while(bsh != NULL){
            if(bsh->next == NULL){
                blmt = newHMelmt(bh->station, bh->value, bh->coord);
                bsh->next = blmt;
                blmt->before = bsh->next; 
                break;
            }
            else if(bh->value > bsh->next->value){
                blmt = newHMelmt(bh->station, bh->value, bh->coord);
                blmt->next = bsh->next;
                bsh->next->before = blmt;
                blmt->before = bsh;
                bsh->next = blmt;
                break;
            }
            bsh = bsh->next;
        }

        bh = bh->next;
        info++;
    }
    printf("\r[sortHMelmt] %d/%d nodes sorted\n", info, max);
    sortedHead->next->before = NULL;
    return sortedHead->next;
}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileDescendingHM_TAB(FILE* file, HMelmt* head){
    HMelmt* bh = head;
    while(bh->next != NULL){ //go to the end
        bh = bh->next;
        
    }
    while(bh != NULL){
        if(fprintf(file, "%d;%d;%s\n", bh->station, bh->value, bh->coord) < 0) exit(340);
        bh = bh->before;
    }   
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileAscendingHM_TAB(FILE* file, HMelmt* head){
    HMelmt* bh = head;
    while(bh != NULL){
        if(fprintf(file, "%d;%d;%s\n", bh->station, bh->value, bh->coord) < 0) exit(341);
        bh = bh->next;
    }   
}

/**
*  \brief Sort a file for -m or -h mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param mode HEIGHTMODE for -h, MOISTUREMODE for -m.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int HeightMoistureMode_TAB(const char* sourcePath, const char* outPath, int mode, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(142);//ERR(102, "Failed to create file '%s'", sourcePath);

    int info = 0; //debug info
    HMelmt *HMelmtHead = NULL;
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
        int sscanfr = 0;
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
        if(sscanfr == 4) HMelmtHead = compileHMData_TAB(HMelmtHead, station, value, coord); //add the new datas
        if(sscanfr == 0) exit(240);
        printf("\r[HeightMoistureMode_TAB] Compiling data %d/?     ", info);

    }
    printf("\r[HeightMoistureMode_TAB] Compiling data DONE. %d datas in %d nodes\n", info, getSizeOfHMelmt(HMelmtHead));

    printf("[HeightMoistureMode_TAB] Sorting List\n");
    HMelmt* HMelmtHeadSorted = sortHMelmt_TAB(HMelmtHead, NULL); //sort the tree by value

    printf("[HeightMoistureMode_TAB] Cleaning up old tree\n");
    freeHMelmtLinkedList(HMelmtHead);
    
    printf("[HeightMoistureMode_TAB] Creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(103);//ERR(103, "Failed to create file '%s'", outPath);
    
    printf("[HeightMoistureMode_TAB] Writting column\n"); //organise column name
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
    
    printf("[HeightMoistureMode_TAB] Writting data\n"); //write data in output file
    if(descending) writeInFileDescendingHM_TAB(out, HMelmtHeadSorted);
    else writeInFileAscendingHM_TAB(out, HMelmtHeadSorted);
    
    printf("[HeightMoistureMode_TAB] Cleaning up\n"); //free ressources
    freeHMelmtLinkedList(HMelmtHeadSorted);
    fclose(source);
    fclose(out);
    printf("[HeightMoistureMode_TAB] DONE\n");
    return 0;
}
