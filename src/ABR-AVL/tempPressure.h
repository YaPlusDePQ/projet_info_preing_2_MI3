#ifndef TEMPRESSUREABRAVL
#define TEMPRESSUREABRAVL

typedef struct stationNode stationNode;
struct stationNode{
    int station;
    float min;
    float max;
    float avg;
    int avgc;
    stationNode* lc;
    stationNode* rc;
    int hl; //balance for AVL
    int hr;
};

typedef struct dateNode dateNode;
struct dateNode{
    char datestr[30];
    long long int dateint;
    stationNode* stationTree;
    dateNode* lc;
    dateNode* rc;
    int hl; //balance for AVL
    int hr;
};

stationNode* newStationNode(int station, float value);

void freeStationNodeTree(stationNode* head);

stationNode* compileStationData(stationNode* head, int station, float value);

int TempPressureMode1ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending);

int TempPressureMode23ABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending);

int TempPressureModeABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending);
#endif