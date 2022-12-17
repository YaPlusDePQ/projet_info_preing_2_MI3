#include "../mainDefine.h"

/**
*  \brief Create and init a node.
*
*  \param dt Type of data stored in the node.
*  \param intInput Integer value for the node, 0 if not use.
*  \param decInput Decimal value for the node, 0 if not use.
*
*  \return pointer to the new node.
*/
node* createNewNode(dataType dt, long long int intInput, double decInput){
    node* newNode = malloc(sizeof(node));
    if(newNode==NULL) ERR(100, "Node memory allocation failed.\n");
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->dt = dt;
    newNode->integer = intInput;
    newNode->decimal = decInput;
    return newNode;
}

