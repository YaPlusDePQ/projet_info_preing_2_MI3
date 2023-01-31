#ifndef WINDABRAVL
#define WINDABRAVL

typedef struct windNode windNode;
struct windNode{
    int station;
    float tVectorX;
    float tVectorY;
    int avgc;
    windNode* lc;
    windNode* rc;
    char coord[30];
    int hl; //balance for AVL
    int hr;
};

int WindModeABRAVL(const char* sourcePath, const char* outPath, int avl, int descending);

#endif