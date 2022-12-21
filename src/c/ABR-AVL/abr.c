#include "../mainDefine.h"

/**
*  \brief add new node to tree who use ABR rule for data.
*
*  \param dt Type of data stored in the node.
*  \param head head of the tree.
*  \param newNode node to add.
*
*  \return new head of the tree.
*/
node* addNewNodeABR(dataType dt, node* head, node* newNode){
    if(head == NULL) return newNode;
    else{
        if(dt!=DEC){
            if(newNode->integer > head->integer){
                if( head->rc != NULL )addNewNodeABR(head->rc, newNode, dt);
                else head->rc = newNode;
            }
            else 
                if( head->lc != NULL )addNewNodeABR(head->lc, newNode, dt);
                else head->lc = newNode;
        }
        else{
            if(newNode->decimal > head->decimal){
                if( head->rc != NULL )addNewNodeABR(head->rc, newNode, dt);
                else head->rc = newNode;
            }
            else 
                if( head->lc != NULL )addNewNodeABR(head->lc, newNode, dt);
                else head->lc = newNode;
        }
        return head;
    }
}

/**
*  \brief get the data of the 1st column of a csv file and store it as a ABR tree.
*
*  \param file stream of the file.
*
*  \return head of the tree.
*/
node* intGetDataFromFileABR(FILE* file){
    node *head = NULL;
    char buffer[1000] = "";
    int value = 0;

    while(fscanf(file,"%d;",&value) && fgets(buffer, 1000, file)){ // get the data of the 1st column and skip the rest of the line
        head = addNewNodeABR(head, createNewNode(INT, value, 0), INT); // create a node from the value and add it to the tree
    }

    return head;
}