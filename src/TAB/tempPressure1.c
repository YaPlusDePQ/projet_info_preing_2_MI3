#include "../mainDefine.h"

stationList* newStationList(int station, float value){
    stationList* newElmt = malloc(sizeof(stationList));
    if(newElmt==NULL) exit(1);//ERR(4, "newStationNode memory allocation failed.\n");
    newElmt->station = station;
    newElmt->min = value;
    newElmt->max = value;
    newElmt->avg = value;
    newElmt->avgc = 1;
    newElmt->next = NULL;
    newElmt->before = NULL;
    //DPRINTF("[newStationNode] [%d]: min:%f, max:%f, avg:%f, avgc:%d", newNode->station, newNode->min, newNode->max, newNode->avg, newNode->avgc);
    return newElmt;
}

void freeStationList(stationList* head){
    if(head->next != NULL){
        freeStationList(head->next);
    }
    free(head);
}

int getSizeOfStationList(stationList* head){
    int i=0;
    while(head!=NULL){
        i++;
        head = head->next;
    }
    return i;
}

stationList* compileStationDataList(stationList* head, int station, float value){
   
    if(head == NULL) return newStationList(station, value); //if the tree doesnt exist (only 1 time)
    
    if(head->station < station){
        stationList* newHead = newStationList(station, value);
        newHead->next = head;
        head->before = newHead;
        return newHead;
    }

    stationList* bh = head;
    stationList* newElement = NULL;
    while(bh != NULL){
        if(bh->station == station){ //update already existing station
            bh->min = value < bh->min ? value : bh->min; 
            bh->max = value > bh->max ? value : bh->max; 
            bh->avg += value;
            bh->avgc++;
            return head;
        }

        if(bh->next == NULL){
            newElement = newStationList(station, value);
            bh->next = newElement;
            newElement->before = bh->next;
            return head;
        }
        else if(station > bh->next->station){
            newElement = newStationList(station, value);
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

void writeInFileDescendingStationList(FILE* file, stationList* head){
    stationList* bh = head;
    while(bh->next != NULL){
        bh = bh->next;
        
    }
    while(bh != NULL){
        if(fprintf(file, "%d;%f;%f;%f\n", bh->station, bh->min, bh->max, bh->avg/bh->avgc) < 0) exit(1);
        bh = bh->before;
    }   
}

void writeInFileAscendingStationList(FILE* file, stationList* head){
    stationList* bh = head;
    while(bh != NULL){
        if(fprintf(file, "%d;%f;%f;%f\n", bh->station, bh->min, bh->max, bh->avg/bh->avgc) < 0) exit(1);
        bh = bh->next;
    }   
}

int TempPressureMode1TAB(const char* sourcePath, const char* outPath, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(1); //ERR(120, "Failed to open file '%s'", sourcePath);

    int info = 0;
    stationList *stationLinkedList = NULL;
    float value = 0;
    int station = 0;
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line
    printf("ok\n");
    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++; 
        value = 0;
        station = 0;
        int sscanfr = 0;
        
        sscanfr=sscanf(line,"%d;%f",&station, &value); // @EDIT FOR ORDER
        if (sscanfr==2) stationLinkedList = compileStationDataList(stationLinkedList, station, value);
        if (sscanfr==0) exit(1); //ERR(1, "Can't read data in line %d.\n", info);
        printf("\r[TempPressureMode1ABRAVL] Compiling data %d/?     ", info);


    }
    printf("\r[TempPressureMode1ABRAVL] Compiling data DONE. %d datas in %d nodes\n", info, getSizeOfStationList(stationLinkedList));

    printf("[TempPressureMode1ABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(1); //ERR(120, "Failed to create file '%s'", outPath);

    printf("[TempPressureMode1ABRAVL] seting up first line\n");
    char st[20] = "";
    char v[20]= "";
    rewind(source);
    fscanf(source, "%[^;\n];%[^;\n]", st, v);
    fprintf(out, "%s;%s min; %s max; %s moyenne\n",st, v, v, v); // @EDIT FOR ORDER

    printf("[TempPressureMode1ABRAVL] writting data\n");
    if(descending) writeInFileDescendingStationList(out, stationLinkedList);
    else writeInFileAscendingStationList(out, stationLinkedList);
    
    printf("[TempPressureMode1ABRAVL] cleaning up\n");
    freeStationList(stationLinkedList);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode1ABRAVL] DONE\n");
    return 0;
}