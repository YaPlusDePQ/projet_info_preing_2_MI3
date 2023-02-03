#ifndef TEMPRESSURETAB
#define TEMPRESSURETAB

/* structure for -t1, -t3, -p1 -p3 modes for linked list data sorting*/
typedef struct stationList stationList;
struct stationList{
    int station;
    float min;
    float max;
    float avg;
    int avgc;
    stationList* next;
    stationList* before;
};

/* structure for -t1, -t3, -p1 -p3 modes for linked list data sorting*/
typedef struct dateList dateList;
struct dateList{
    char datestr[30]; 
    long long int dateint; 
    stationList* stationLinkedList;
    dateList* next;
    dateList* before;
};

stationList* newStationList(int station, float value);

void freeStationList(stationList* head);

stationList* compileStationDataList(stationList* head, int station, float value);

int TempPressureMode1TAB(const char* sourcePath, const char* outPath, int descending);

int TempPressureMode_TAB(const char* sourcePath, const char* outPath, int mode, int descending);

#endif