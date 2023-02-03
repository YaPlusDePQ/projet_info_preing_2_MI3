#ifndef HEIGHTMOISTURETAB
#define HEIGHTMOISTURETAB

typedef struct HMList HMList;
/* structure for -h -m mode for ABR and AVL data sorting*/
struct HMList{
    int station; //id of the station
    int value; //height of the station/Moisture of the station
    HMList* next; //left child
    HMList* before; //right child
    char coord[30]; //char space for coordinate storage
};

#endif