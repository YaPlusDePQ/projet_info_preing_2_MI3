#ifndef ABR
#define ABR

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

#endif