#include "../mainDefine.h"


dateList* newDateList(const char* date, long long int dateint, int station, float value){
    dateList* newElmt  =  malloc(sizeof(dateList));
    if(newElmt==NULL) exit(1);
    strcpy(newElmt->datestr, date);
    newElmt->dateint = dateint;
    newElmt->stationLinkedList = newStationList(station, value);
    newElmt->next = NULL;
    newElmt->before = NULL;
    return newElmt;
}

void freeDateList(dateList* head){
    if(head->next != NULL){
        freeDateList(head->next);
    }
    freeStationList(head->stationLinkedList);
    free(head);
}

int getSizeOfDateList(dateList* head){
    int i=0;
    while(head!=NULL){
        i++;
        head = head->next;
    }
    return i;
}

dateList* compiledateData_TAB(int mode, dateList* head, const char* date, long long int dateint, int station, float value){
   
    if(head == NULL) return newDateList(date, dateint, station, value);
    
    if(head->dateint < dateint){
        dateList* newHead = newDateList(date, dateint, station, value);
        newHead->next = head;
        head->before = newHead;
        return newHead;
    }

    dateList* bh = head;
    dateList* newElement = NULL;

    while(bh != NULL){
        if(bh->dateint == dateint){ //update already existing station
            switch(mode){
                case 2:
                    head->stationLinkedList->avg += value;
                    head->stationLinkedList->avgc++;
                    break;
                case 3:
                    head->stationLinkedList = compileStationDataList(head->stationLinkedList, station, value);
                    break;
            }
            return head;
        }

        if(bh->next == NULL){
            newElement = newDateList(date, dateint, station, value);
            bh->next = newElement;
            newElement->before = bh->next;
            return head;
        }
        else if(dateint > bh->next->dateint){
            newElement = newDateList(date, dateint, station, value);
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

void writeInFileStationListTP23_TAB(FILE* file, const char* date, stationList* head){
    stationList* bh = head;
    while(bh != NULL){
        if(fprintf(file, "%s;%d;%f\n", date, head->station, head->avg/head->avgc)< 0) exit(1);
        bh = bh->next;
    }   
}

void writeInFileDescendingTP23L_TAB(FILE* file, int mode, dateList* head){
    dateList* bh = head;
    while(bh->next != NULL){
        bh = bh->next;
        
    }
    while(bh != NULL){
        switch(mode){
            case 2:
                if(fprintf(file, "%s;%f\n", bh->datestr, bh->stationLinkedList->avg/bh->stationLinkedList->avgc)< 0) exit(350);// @EDIT FOR ORDER
                break;
            case 3:
                writeInFileStationListTP23_TAB(file, bh->datestr, bh->stationLinkedList);
                fputs("\n\n", file);
                break;
        }
        bh = bh->before;
    }   
}

void writeInFileAscendingTP23L_TAB(FILE* file, int mode, dateList* head){
    dateList* bh = head;
    while(bh != NULL){
            switch(mode){
            case 2:
                if(fprintf(file, "%s;%f\n", bh->datestr, bh->stationLinkedList->avg/bh->stationLinkedList->avgc)< 0) exit(351);// @EDIT FOR ORDER
                break;
            case 3:
                writeInFileStationListTP23_TAB(file, bh->datestr, bh->stationLinkedList);
                fputs("\n\n", file);
                break;
        }
        bh = bh->next;
    }   
}

int TempPressureMode23_TAB(const char* sourcePath, const char* outPath, int mode, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(1);

    int info = 0;
    dateList *dateLinkedList = NULL;
    float value = 0;
    int station = 0;
    char date[30] = "";
    char line[1000] = ""; //line buffer

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++;
        value = 0;
        station = 0;
        int sscanfr=0;
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
                exit(1);
                break;
            case 2:
                if(mode==2) dateLinkedList = compiledateData_TAB(mode, dateLinkedList, date, dateToInt(date), station, value);
                break;
            case 3:
                if(mode==3) dateLinkedList = compiledateData_TAB(mode, dateLinkedList, date, dateToInt(date), station, value);
                break;
        }
       
        printf("\r[TempPressureMode23_TAB] Compiling data %d/?     ", info);
    }
    printf("\r[TempPressureMode23_TAB] Compiling data DONE. %d datas in %d nodes\n", info, getSizeOfDateList(dateLinkedList));

    printf("[TempPressureMode23_TAB] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(1);//ERR(120, "Failed to create file '%s'", outPath);

    printf("[TempPressureMode23_TAB] seting up first line\n");
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
    
    printf("[TempPressureMode23_TAB] writting data\n");
    if(descending) writeInFileDescendingTP23L_TAB(out, mode, dateLinkedList);
    else writeInFileAscendingTP23L_TAB(out, mode, dateLinkedList);
    
    printf("[TempPressureMode23_TAB] cleaning up\n");
    freeDateList(dateLinkedList);
    fclose(source);
    fclose(out);
    printf("[TempPressureMode23_TAB] DONE\n");
    return 0;
}

int TempPressureMode_TAB(const char* sourcePath, const char* outPath, int mode, int descending){
    if(mode==1) TempPressureMode1TAB(sourcePath, outPath, descending);
    else TempPressureMode23_TAB(sourcePath, outPath, mode, descending);
    return 0;
}