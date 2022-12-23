#ifndef ABR
#define ABR

node* addNewNodeABR(dataType dt, node* head, node* newNode);

node* BuildABRFromFile(const char* sourcePath);

void BuildFileFromABR(node* head, const char* sourcePath, const char* outPath, int descending);

#endif