#ifndef WINDABRAVL
#define WINDABRAVL

/* structure for -w modes for ABR and AVL data sorting*/
typedef struct windNode windNode;
struct windNode{
    int station;
    float tDirection; // sum of all direction of wind
    float tSpeed; // sum of all direction of wind
    int avgc; //value counter for average calculation
    windNode* lc;
    windNode* rc;
    char coord[30];
    int hl;
    int hr;
};

int WindMode_ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending);

#endif