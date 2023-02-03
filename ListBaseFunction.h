#ifndef LISTBASEFUNCTION
#define LISTBASEFUNCTION
#include "../mainDefine.h"

typedef struct list{
    long long int elem1;
    float elem2;
    float elem3;
    int min;
    int max;
    int lon;
    int lat;
    float average;
    struct list * next;
}List;

List * ListCreation(long long int a, float b, float c, int lat, int lon);                              //To create a list with it's first link (including 3 rows, latitude, longitude)

List* ListInsertEnd(List * plist, long long int a,float b, float c, int lat, int lon);                 //To insert a link (3 rows, latitude, longitude) to the list, at the end of it 

void DisplayList(List * plist);                                 //To display the list

List * DeleteBeginning(List * plist);                           //Deletes the first link in a list

List * DeleteEnd(List * plist);                                 //Deletes the last link in a list

List * DeleteMiddle(List * plist, int pos);                     //Deletes a link in the middle of the list

List *  Del(List * plist, int sup);                             //Deletes a link in a list no matter it's position

int occurence(List * plist, int sup);                           //Returns the number of times a value (first row) appears into the list

List * DeleteAllOccurences(List * pliste, int sup, int occur);  //Deletes all the occurences of a value (in the first) in a list , no matter if it's at the begginning, the middle or the end 

#endif