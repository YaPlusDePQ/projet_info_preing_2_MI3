#include "../mainDefine.h"

windList* newWindList(int station, float direction, float speed, const char* coord){
    windList* newElmt = malloc(sizeof(windList));
    if(newElmt==NULL) exit(1);//ERR(4, "newWindNode memory allocation failed.\n");
    newElmt->next = NULL;
    newElmt->before = NULL;
    newElmt->station = station;
    newElmt->tDirection = direction;
    newElmt->tSpeed = speed;
    newElmt->avgc = 1;
    strcpy(newElmt->coord, coord);
    //DPRINTF("[newHMNode] [%d]: %f %f %s\n",newNode->station, newNode->tDirection, newNode->tSpeed, newNode->coord);
    return newElmt;
}

void freeWindList(windList* head){
    if(head->next != NULL){
        freeWindList(head->next);
    }
    free(head);
}

int getSizeOfWindList(windList* head){
    int i=0;
    while(head!=NULL){
        i++;
        head = head->next;
    }
    return i;
}

windList* compileWindDataList(windList* head, int station, float direction, float speed, const char* coord){
   
    if(head == NULL) return newWindList(station, direction, speed, coord); //if the tree doesnt exist (only 1 time)
    
    if(head->station < station){
        windList* newHead = newWindList(station, direction, speed, coord);
        newHead->next = head;
        head->before = newHead;
        return newHead;
    }

    windList* bh = head;
    windList* newElement = NULL;
    while(bh != NULL){
        if(bh->station == station){ //update already existing station
            bh->tDirection += direction;
            bh->tSpeed += speed; 
            bh->avgc++;
            if( !strcmp(head->coord, "")) strcpy(head->coord, coord);
            return head;
        }

        if(bh->next == NULL){
            newElement = newWindList(station, direction, speed, coord);
            bh->next = newElement;
            newElement->before = bh->next;
            return head;
        }
        else if(station > bh->next->station){
            newElement = newWindList(station, direction, speed, coord);
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

void writeInFileDescendingWindList(FILE* file, windList* head){
    windList* bh = head;
    while(bh->next != NULL){
        bh = bh->next;
        
    }
    while(bh != NULL){
        if(fprintf(file, "%d;%f;%f;%s\n", bh->station, bh->tDirection/bh->avgc, bh->tSpeed/bh->avgc, bh->coord) < 0) exit(1);
        bh = bh->before;
    }   
}

void writeInFileAscendingWindList(FILE* file, windList* head){
    windList* bh = head;
    while(bh != NULL){
        if(fprintf(file, "%d;%f;%f;%s\n", bh->station, bh->tDirection/bh->avgc, bh->tSpeed/bh->avgc, bh->coord) < 0) exit(1);
        bh = bh->next;
    }   
}

int WindModeTAB(const char* sourcePath, const char* outPath, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(1);//ERR(120, "Failed to create file '%s'", sourcePath);

    int info = 0;
    windList *windList = NULL;
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
        int sscanfr = 0;
        strcpy(coord, "");
        
        sscanfr = sscanf(line,"%d;%f;%f;%[^\n]",&station, &windDirection, &windSpeed, coord);// @EDIT FOR ORDER
        if(sscanfr==4) windList = compileWindDataList(windList, station, windDirection, windSpeed, coord);
        if(sscanfr==0) exit(1);//ERR(1, "Can't read data in line %d.\n", info);
        printf("\r[WindModeABRAVL] Compiling data %d/?", info);

    }
    printf("\r[WindModeABRAVL] Compiling data DONE. %d datas in %d nodes                \n", info, getSizeOfWindList(windList));

    printf("[WindModeABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(1);//ERR(120, "Failed to create file '%s'", outPath);

    fputs("ID OMM station;direction moyenne; vitesse moyenne;X;Y\n", out);

    printf("[WindModeABRAVL] writting data\n");
    if(descending) writeInFileDescendingWindList(out, windList);
    else writeInFileAscendingWindList(out, windList);
    
    printf("[WindModeABRAVL] cleaning up\n");
    freeWindList(windList);
    fclose(source);
    fclose(out);
    printf("[WindModeABRAVL] DONE\n");
    return 0;
}