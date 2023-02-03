#ifndef WINDTAB
#define WINDTAB

typedef struct windList windList;
struct windList{
    int station;
    float tDirection;
    float tSpeed;
    int avgc;
    windList* next;
    windList* before;
    char coord[30];
};

int WindModeTAB(const char* sourcePath, const char* outPath, int descending);


#endif