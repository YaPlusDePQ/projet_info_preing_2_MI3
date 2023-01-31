#ifndef HEIGHTMOISTUREABRAVL
#define HEIGHTMOISTUREABRAVL

#define HEIGHTMODE 0
#define MOISTUREMODE 1

typedef struct HMNode HMNode;
struct HMNode{
    int station;
    int value;
    HMNode* lc;
    HMNode* rc;
    char coord[30];
    int hl; //balance for AVL
    int hr;
};

int HeightMoistureModeABRAVL(const char* sourcePath, const char* outPath, int avl, int mode, int descending);
#endif