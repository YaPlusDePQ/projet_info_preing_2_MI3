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
    DPRINTF("[createNewNode] new Node created at %p:[%s] [%I64d] [%.3f]\n", newNode, newNode->dt==INT ? "INT" : newNode->dt==DEC ? "DEC" : "DATE", newNode->integer, newNode->decimal);
    return newNode;
}

/**
*  \brief free binary tree.
*
*  \param head head of the binary tree.
*/
void freeAllNode(node* head){
    if(head->lc != NULL) freeAllNode(head->lc); //free all left child
    if(head->rc != NULL) freeAllNode(head->rc); //free all right child
    DPRINTF("[freeNode] freeing %p ", head);
    if(head != NULL){
        free(head);
        DPRINTF("[DONE]\n");
    }
    else{
        DPRINTF("[FAILED]\n");
        ERR(101, "Impossible value for head imply memory leak or losing track of head during process.");
    }
    
}

/**
*  \brief recurcive call for printfNode.
*
*  \param dt Type of data stored in the node.
*  \param node Node to print.
*  \param level depth of node.
*/
void _printfNodeRCall(dataType dt, node* node, int level){
    for(int i=1; i<level; i++){
        printf(" |");
    }
    if(level != 0 ) printf(" \\_");
   
    if(dt!=DEC) printf("%I64d\n", node->integer);
    else printf("%.3f\n", node->decimal);
    
    if(node->rc!=NULL) _printfNodeRCall(dt, node->rc, level+1);
    if(node->lc!=NULL) _printfNodeRCall(dt, node->lc, level+1);
}

/**
*  \brief print tree.
*
*  \param dt Type of data stored in the node.
*  \param head tree to print.
*/
void printfNode(dataType dt, node* head){
    _printfNodeRCall(dt, head, 0);
}