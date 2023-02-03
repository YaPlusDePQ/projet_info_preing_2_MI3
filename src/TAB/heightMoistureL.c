#include "../mainDefine.h"

HMList* newHMlist(int station, int value, const char* coord){
    HMList* newNode = malloc(sizeof(HMList));
    if(newNode==NULL) exit(1);//ERR(100, "newHMNode memory allocation failed.\n");
    newNode->next = NULL;
    newNode->before = NULL;
    newNode->station = station;
    newNode->value = value;
    strcpy(newNode->coord, coord);
    return newNode;
}


void freeHMListt(HMList* head){
    if(head->next != NULL){
        freeHMListt(head->next);
    }
    free(head);
}

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
HMList* compileHMDataList(HMList* head, int station, int value, const char* coord){
   
    if(head == NULL) return newHMlist(station, value, coord); //if the tree doesnt exist (only 1 time)
    
    if(head->station < station){
        HMList* newHead = newHMlist(station, value, coord);
        newHead->next = head;
        head->before = newHead;
        return newHead;
    }

    HMList* bh = head;
    HMList* newElement = NULL;
    while(bh != NULL){
        if(bh->station == station){ //update already existing station
            bh->value = value > bh->value ? value : bh->value; 
            if( !strcmp(bh->coord, "")) strcpy(bh->coord, coord);
            return head;
        }

        if(bh->next == NULL){
            newElement = newHMlist(station, value, coord);
            bh->next = newElement;
            newElement->before = bh->next;
        }
        else if(station > bh->next->station){
            newElement = newHMlist(station, value, coord);
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


HMList* sortHMList(HMList* head, HMList* sortedHead){
    HMList* bh = head;
    sortedHead = newHMlist(head->station, head->value, head->coord);
    HMList* bsh = sortedHead;
    HMList* blmt = NULL;

    while(bh != NULL){
        blmt = NULL;
        bsh = sortedHead;

        while(bsh != NULL){
            if(bsh->next == NULL){
                blmt = newHMlist(bh->station, bh->value, bh->coord);
                bsh->next = blmt;
                blmt->before = bsh->next; 
                break;
            }
            else if(bh->value > bsh->next->value){
                blmt = newHMlist(bh->station, bh->value, bh->coord);
                blmt->next = bsh->next;
                bsh->next->before = blmt;
                blmt->before = bsh;
                bsh->next = blmt;
                break;
            }
        }

        bh = bh->next;
        
    }

    return sortedHead;
}

void writeInFileDescendingHMList(FILE* file, HMList* head){
    HMList* bh = head;
    while(head->next != NULL){
        bh = bh->next;
    }
    while(bh != NULL){
        if(fprintf(file, "%d;%d;%s\n", bh->station, bh->value, bh->coord) < 0) exit(300);
        bh = bh->before;
    }   
}

void writeInFileAscendingHMList(FILE* file, HMList* head){
    HMList* bh = head;
    while(bh != NULL){
        if(fprintf(file, "%d;%d;%s\n", bh->station, bh->value, bh->coord) < 0) exit(300);
        bh = bh->next;
    }   
}

int HeightMoistureModeTAB(const char* sourcePath, const char* outPath, int mode, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(102);//ERR(102, "Failed to create file '%s'", sourcePath);

    int info = 0; //debug info
    HMList *HMList = NULL;
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
        if(sscanfr == 4) HMList = compileHMDataList(HMList, station, value, coord); //add the new datas
        if(sscanfr == 0) exit(200);//ERR(200, "Can't read data in line %d.\n", info);
        printf("\r[HeightMoistureModeTAB] Compiling data %d/?     ", info);

    }
    printf("\r[HeightMoistureModeABRAVL] Compiling data DONE. %d datas\n", info);

//     printf("[HeightMoistureModeABRAVL] Sorting List\n");
//     HMList* scalbnf = sortHMList(HMList, NULL); //sort the tree by value

//     printf("[HeightMoistureModeABRAVL] Cleaning up old tree\n");
//     freeHMListt(HMList);
    
//     printf("[HeightMoistureModeABRAVL] Creating output file\n");
//     FILE* out = fopen(outPath, "w");
//     if(out == NULL) exit(103);//ERR(103, "Failed to create file '%s'", outPath);
    
//     printf("[HeightMoistureModeABRAVL] Writting column\n"); //organise column name
//     char c0[20] = "";
//     char c1[20]= "";
//     char c2[20]="";
//     char c3[20]="";
//     rewind(source);
//     fscanf(source, "%[^;\n];%[^;\n];%[^;\n];%[^;\n]", c0, c1, c2, c3);
//     switch(mode){ //make sure that column are in the same order as the data
//         case HEIGHTMODE:
//             fprintf(out, "%s;%s max;%s;%s\n", c0,c3,c1,c2);
//             break;
//         case MOISTUREMODE:
//             fprintf(out, "%s;%s max;%s;%s\n", c0,c1,c2,c3);
//             break;  
//     }
    
//     printf("[HeightMoistureModeABRAVL] Writting data\n"); //write data in output file
//     if(descending) writeInFileDescendingHMList(out, sortedHMList);
//     else writeInFileAscendingHMList(out, sortedHMList);
    
//     printf("[HeightMoistureModeABRAVL] Cleaning up\n"); //free ressources
//     freeHMListt(sortedHMList);
//     fclose(source);
//     fclose(out);
//     printf("[HeightMoistureModeABRAVL] DONE\n");
//     return 0;
    return 0;
}
