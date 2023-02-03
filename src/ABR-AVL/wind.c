#include "../mainDefine.h"

/* -------------------------------------------- windNode strcuture dependency -------------------------------------------- */
/**
*  \brief Create new windNode element.
*
*  \param station Station id.
*  \param direction direction of wind of the station.
*  \param speed speed of wind of the station.
*  \param coord Coordinate of the station.
*
*  \return Pointer to the new element.
*/
windNode* newWindNode(int station, float direction, float speed, const char* coord){
    windNode* newNode = malloc(sizeof(windNode));
    if(newNode==NULL) exit(130);
    newNode->lc = NULL;
    newNode->rc = NULL;
    newNode->station = station;
    newNode->tDirection = direction;
    newNode->tSpeed = speed;
    newNode->avgc = 1;
    newNode->hl = 0;
    newNode->hr = 0;
    strcpy(newNode->coord, coord);
    return newNode;
}

/**
*  \brief free windNode tree.
*  
*  \param head head of the tree.
*/
void freeWindNodeTree(windNode* head){
    if(head->lc != NULL) freeWindNodeTree(head->lc); //free all left child
    if(head->rc != NULL) freeWindNodeTree(head->rc); //free all right child
    if(head != NULL){
        free(head);
    }
    else{
        exit(131);
    }
}

/**
*  \brief Give number of node of a windNode tree.
*  
*  \param head Head of the tree.
*
*  \return Number of node(s).
*/
int SizeOfWindNodeTree(windNode* head, int i){
    i++;
    if(head->lc != NULL) i = SizeOfWindNodeTree(head->lc, i); 
    if(head->rc != NULL) i = SizeOfWindNodeTree(head->rc, i);
    return i;
}

/*  -------------------------------------------- AVL function -------------------------------------------- */

/**
*  \brief Set height of each node of a windNode tree.
*  
*  \param head Head of the tree.
*
*  \return Height of the tree.
*/
int setHeightWindNode(windNode* head){
    if(head == NULL) return 0;
    else{
        int hlc = setHeightWindNode(head->lc);
        int hrc = setHeightWindNode(head->rc);

        head->hl = hlc;
        head->hr = hrc;
        return ( hlc > hrc ? hlc : hrc)+1;
    }
}

/**
*  \brief Right rotation balancing of a windNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
windNode* RightRotationWindNodeTree(windNode* unstablehead){
    windNode* newhead = unstablehead->rc;
    unstablehead->rc = newhead->lc;
    newhead->lc = unstablehead;
    return newhead;
}

/**
*  \brief Left rotation balancing of a windNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
windNode* LeftRotationWindNodeTree(windNode* unstablehead){
    windNode* newhead = unstablehead->lc;
    unstablehead->lc = newhead->rc;
    newhead->rc = unstablehead;
    return newhead;
}

/**
*  \brief "Double right" rotation balancing of a windNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
windNode* DRightRotationWindNodeTree(windNode* unstablehead){
    unstablehead->rc = LeftRotationWindNodeTree(unstablehead->rc);
    return RightRotationWindNodeTree(unstablehead); 
}

/**
*  \brief "Double left" rotation balancing of a windNode tree.
*  
*  \param unstableNode Node that need balancing.
*
*  \return Balanced Node.
*/
windNode* DLeftRotationWindNodeTree(windNode* unstablehead){
    unstablehead->lc = RightRotationWindNodeTree(unstablehead->lc);
    return LeftRotationWindNodeTree(unstablehead);
}

/**
*  \brief Test if a windNode tree need balancing.
*  
*  \param head Head of the tree.
*
*  \return 0 if balanced, 1 otherwise.
*/
int isUnbalancedWindNodeTree(windNode *head){
    if(head == NULL) return 0;
    if((head->hl - head->hr)  < -1 || (head->hl - head->hr) > 1) return 1;
    return isUnbalancedWindNodeTree(head->lc) || isUnbalancedWindNodeTree(head->rc);
}

/**
*  \brief Balanced a windNode tree 1 time.
*  
*  \param head Head of the tree.
*
*  \return New windNode tree's head.
*/
windNode* BalanceWindNodeTree(windNode* head){
    if(head == NULL) return NULL;

    if((head->hl - head->hr) < -1 || (head->hl - head->hr) > 1){
        if((head->hl - head->hr) < -1){
            
            if( head->rc != NULL && head->rc->hl > head->rc->hr) head = DRightRotationWindNodeTree(head);
            else head = RightRotationWindNodeTree(head);
        }
        else{
            if( head->lc != NULL && head->lc->hr > head->lc->hl)  head = DLeftRotationWindNodeTree(head);
            else head = LeftRotationWindNodeTree(head);
        }

        return head;
    }
    head->lc = BalanceWindNodeTree(head->lc);
    head->rc = BalanceWindNodeTree(head->rc);

    return head;
}

/* -------------------------------------------- sorting functions --------------------------------------------*/

/**
*  \brief Add new windNode only if the station isn't in the tree, if it is in, update the values.
*  
*  \param station Station id.
*  \param direction direction of wind of the station.
*  \param speed speed of wind of the station.
*  \param coord Coordinate of the station.
*
*  \return New windNode tree's head.
*/
windNode* compileWindData_ABRAVL(windNode* head, int station, float direction, float speed, const char* coord){
    if(head == NULL) return newWindNode(station, direction, speed, coord);
    
    if(head->station == station) {
        head->tDirection += direction;
        head->tSpeed += speed; 
        head->avgc++;
        if( !strcmp(head->coord, "")) strcpy(head->coord, coord);
        return head;
    }

    if(station <= head->station){
        if(head->lc != NULL) compileWindData_ABRAVL(head->lc, station, direction, speed, coord);
        else head->lc = newWindNode(station, direction, speed, coord);
    }
    else{
        if(head->rc != NULL) compileWindData_ABRAVL(head->rc, station, direction, speed, coord);
        else head->rc = newWindNode(station, direction, speed, coord);
    }

    return head;
}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileDescendingW_ABRAVL(FILE* file, windNode* current){
    if(current->rc != NULL) writeInFileDescendingW_ABRAVL(file, current->rc);
    if(fprintf(file, "%d;%f;%f;%s\n", current->station, current->tDirection/current->avgc, current->tSpeed/current->avgc, current->coord) < 0) exit(330);// @EDIT FOR ORDER
    if(current->lc != NULL) writeInFileDescendingW_ABRAVL(file, current->lc);
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void writeInFileAscendingW_ABRAVL(FILE* file, windNode* current){
    if(current->lc != NULL) writeInFileAscendingW_ABRAVL(file, current->lc);
    if(fprintf(file, "%d;%f;%f;%s\n", current->station, current->tDirection/current->avgc, current->tSpeed/current->avgc, current->coord) < 0) exit(331);// @EDIT FOR ORDER
    if(current->rc != NULL) writeInFileAscendingW_ABRAVL(file, current->rc);
}

/**
*  \brief Sort a file for -w mode using ABR or AVL.
*  
*  \param sourcePath Path of the source file.
*  \param outPath Path of the output file.
*  \param avl 0 for ABR sorting, 1 for AVL sorting.
*  \param descending 0 for Ascending order of value, 1 for descending order of value.
*
*  \return 0.
*/
int WindMode_ABRAVL(const char* sourcePath, const char* outPath, int avl, int descending){
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) exit(132);

    int info = 0;
    windNode *windTree = NULL;
    int station = 0;
    float windDirection = 0;
    float windSpeed = 0;
    char coord[30] = "";
    char line[1000] = ""; //line buffer
    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        info++;
        station = 0;
        windDirection = 0;
        windSpeed = 0;
        int sscanfr = 0;
        strcpy(coord, "");
        
        sscanfr = sscanf(line,"%d;%f;%f;%[^\n]",&station, &windDirection, &windSpeed, coord);// @EDIT FOR ORDER
        if(sscanfr==4) windTree = compileWindData_ABRAVL(windTree, station, windDirection, windSpeed, coord);
        if(sscanfr==0) exit(230);
        printf("\r[WindMode_ABRAVL] Compiling data %d/?", info);

        if(avl){
            printf("Balancing tree...");
            setHeightWindNode(windTree);
            while(isUnbalancedWindNodeTree(windTree)){
                windTree = BalanceWindNodeTree(windTree);
                setHeightWindNode(windTree);
                
            }
        }
    }
    printf("\r[WindMode_ABRAVL] Compiling data DONE. %d datas in %d nodes                \n", info, SizeOfWindNodeTree(windTree, 0));

    printf("[WindMode_ABRAVL] creating output file\n");
    FILE* out = fopen(outPath, "w");
    if(out == NULL) exit(123);

    fputs("ID OMM station;direction moyenne; vitesse moyenne;X;Y\n", out);

    printf("[WindMode_ABRAVL] writting data\n");
    if(descending) writeInFileDescendingW_ABRAVL(out, windTree);
    else writeInFileAscendingW_ABRAVL(out, windTree);
    
    printf("[WindMode_ABRAVL] cleaning up\n");
    freeWindNodeTree(windTree);
    fclose(source);
    fclose(out);
    printf("[WindMode_ABRAVL] DONE\n");
    return 0;
}
