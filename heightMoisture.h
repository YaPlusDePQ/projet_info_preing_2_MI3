#ifndef HEIGHTMOISTUREABRAVL
#define HEIGHTMOISTUREABRAVL

#define HEIGHTMODE 0
#define MOISTUREMODE 1

typedef struct HMNode HMNode;
/* structure for -h -m mode for ABR and AVL data sorting*/
struct HMNode{
    int station; //id of the station
    int value; //height of the station/Moisture of the station
    HMNode* lc; //left child
    HMNode* rc; //right child
    char coord[30]; //char space for coordinate storage
    int hl; //height of left child
    int hr; //height of right child
};

int HeightMoistureModeABRAVL(const char* sourcePath, const char* outPath, int mode, int avl, int descending);
#endif