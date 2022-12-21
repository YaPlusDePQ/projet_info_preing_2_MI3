#ifndef NODE
#define NODE

/* help to flag data */
typedef enum dataType dataType;
enum dataType{DATE, INT, DEC};

/* structure for binary tree */
typedef struct node node;
struct node{
    node* lc; // left child
    node* rc; // right child
    dataType dt; // type of data stored in the node
    long long int integer; // variable for integer and date (long long int because date will be store as second)
    double decimal; // variable for decimal
};

node* createNewNode(dataType dt, long long int intInput, double decInput);

void freeAllNode(node* head);

// _printfNodeRCall not present to prevent call

void printfNode(dataType dt, node* head);

#endif