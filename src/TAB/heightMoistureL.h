#ifndef HEIGHTMOISTURETAB
#define HEIGHTMOISTURETAB

typedef struct HMelmt HMelmt;
/* structure for -h -m mode for linked list data sorting*/
struct HMelmt{
    int station; //id of the station
    int value; //height of the station/Moisture of the station
    HMelmt* next; //next element
    HMelmt* before; //element before
    char coord[30]; //char space for coordinate storage
};

int HeightMoistureMode_TAB(const char* sourcePath, const char* outPath, int mode, int descending);

#endif