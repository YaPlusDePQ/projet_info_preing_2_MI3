#ifndef LIST
#define LIST

typedef struct list{
    int elem1;
    int elem2;
    struct list * next;
}List;

List * ListCreation(int a, int b);

List* ListInsertEnd(List * plist, int a,int b);

void DisplayList(List * plist);

List * FileIntoList(FILE * file);

FILE* ListIntoFile(List * plist);

int ChecksSortedAscending(List * plist);

int ChecksSortedDescending(List * plist);

List * SortAscending(List *plist);

List * SortDescending(List *plist);

#endif 