#ifndef TEMPRESSUREABRAVL
#define TEMPRESSUREABRAVL

/* structure for -t1, -t3, -p1 -p3 modes for ABR and AVL data sorting*/
typedef struct stationNode stationNode;
struct stationNode{
    int station; //id of the station
    float min; 
    float max; 
    float avg; //average
    int avgc; //value counter for average calculation
    stationNode* lc; //left child
    stationNode* rc; //right child
    int hl; //height of left child
    int hr; //height of right child
};

/* structure for -t1, -t3, -p1 -p3 modes for ABR and AVL data sorting*/
typedef struct dateNode dateNode;
struct dateNode{
    char datestr[30]; //date in the format of the file
    long long int dateint; //date in hours
    stationNode* stationTree; //store average of all time for t2/p2 and a stationTree for t3/p3
    dateNode* lc;
    dateNode* rc;
    int hl; 
    int hr; 
};

stationNode* newStationNode(int station, float value);

void freeStationNodeTree(stationNode* head);

stationNode* compileStationData_ABRAVL(stationNode* head, int station, float value);

int TempPressureMode1_ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending);

int TempPressureMode23_ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending);

int TempPressureMode_ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending);
#endif