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
node* createNewNode(dataType dt, long long int intInput, double decInput, char line[1000]){
    node* newNode = malloc(sizeof(node));
    if(newNode==NULL) ERR(100, "Node memory allocation failed.\n");
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->dt = dt;
    newNode->integer = intInput;
    newNode->decimal = decInput;
    strcpy(newNode->line, line);
    DPRINTF("[createNewNode] new Node created at %p:[%s] [%I64d] [%.3f] [%s]\n", newNode, newNode->dt==INT ? "INT" : newNode->dt==DEC ? "DEC" : "DATE", newNode->integer, newNode->decimal, newNode->line);
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
*  \brief Recurcive call for printfNode.
*
*  \param dt Type of data stored in the node.
*  \param current Current node during recursion.
*  \param level Depth of node.
*/
void _printfNodeRCall(dataType dt, node* current, int level){
    if(current!=NULL) _printfNodeRCall(dt, current->rc, level+1);

    for(int i=0; i<level; i++){
        printf("  ");
    }
    if(current!=NULL){
        if(dt!=DEC) printf("%I64d\n", current->integer);
        else printf("%.3f\n", current->decimal);
    }
    else printf("NULL\n");
    
    if(current!=NULL) _printfNodeRCall(dt, current->lc, level+1);
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