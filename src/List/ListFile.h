#ifndef LISTFILE
#define LISTFILE
#include "../mainDefine.h"

List * FileIntoList2(FILE * file, int op);              //gets the 2 rows into the list, the 2 rows are into one link - for options 1 (op=1) and option 2 (op=2)

List * FileIntoList3(FILE * file);                      //gets the 3 rows into the list, the 3 rows are into one link - for options 3

List * FileIntoList4(FILE * file, int op);              //gets the 4 rows into the list, the 4 rows are into one link - for the height (op=1) and moisture (op=2)

List * FileIntoList5(FILE * file);                      //gets the 5 rows into the list, the 5 rows are into one link - for the wind

FILE* ListIntoFile(List * plist, FILE * end, int option);           //puts the wanted rows into a .dat file - for every option except option 3

FILE* ListIntoFile2(List * plist, FILE * end);           //puts the wanted rows into a .dat file - for option 3
#endif