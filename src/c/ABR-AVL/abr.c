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
        if(dt==DEC ? newNode->decimal > head->decimal : newNode->integer > head->integer){ //genjutsu interdit
            if( head->rc != NULL )addNewNodeABR(dt, head->rc, newNode);
            else head->rc = newNode;
        }
        else{
            if( head->lc != NULL )addNewNodeABR(dt,head->lc, newNode);
            else head->lc = newNode;
        }
    }
    return head;
}

/**
*  \brief Get the data of the 1st column of a csv file and store it as a ABR tree.
*
*  \param sourcePath Path to file.
*
*  \return Head of the tree.
*/
node* BuildABRFromFile(const char* sourcePath){ //only int for now
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(120, "Failed to create file '%s'", sourcePath);

    node *head = NULL;
    dataType dt;
    char line[1000] = ""; //line buffer
    char data[1000] = ""; //data from line buffer
    long long int valueNoDec = 0;
    double valueDec = 0;

    fgets(line, 1000, source); //skip first line

    while(fgets(line, 1000, source)){ //make sure that te whole line is read
        valueNoDec = 0;
        valueDec = 0;

        sscanf(line,"%s;",data); //extract raw data from line
        switch(dt=getDataTypeFromChar(data)){
            case INT:
                sscanf(data,"%I64d",&valueNoDec);
                break;
            case DEC:
                sscanf(data,"%lf",&valueDec);
                break;
            case DATE:
                valueNoDec = dateToInt(data);
                break;
        }

        node* newNode = createNewNode(dt, valueNoDec, valueDec, line);
        head = addNewNodeABR(dt, head, newNode); // create a node from the value and add it to the tree
    }
    fclose(source);
    return head;
}

/**
*  \brief Recursive call for writing in a descending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void _writeInFileDescendingABR(FILE* file, node* current){
    if(current->lc != NULL) _writeInFileDescendingABR(file, current->lc);
    if(fputs(current->line, file) == EOF) ERR(301, "Failed to write '%s' in file.", current->line);
    if(current->rc != NULL) _writeInFileDescendingABR(file, current->rc);
}

/**
*  \brief Recursive call for writing in a Ascending order.
*
*  \param file Target file.
*  \param current Current node during recursion.
*
*/
void _writeInFileAscendingABR(FILE* file, node* current){
    if(current->rc != NULL) _writeInFileAscendingABR(file, current->rc);
    if(fputs(current->line, file) == EOF) ERR(302, "Failed to write '%s' in file.", current->line);
    if(current->lc != NULL) _writeInFileAscendingABR(file, current->lc);
}


/**
*  \brief Write data of the tree in file.
*
*  \param head head of the tree.
*  \param sourcePath source file path.
*  \param outPath output file path.
*  \param descending if 1 value will be in descending order.
*
*/
void BuildFileFromABR(node* head, const char* sourcePath, const char* outPath, int descending){
    FILE* out = fopen(outPath, "w");
    if(out == NULL) ERR(121, "Failed to create file '%s'.", outPath);
    FILE* source = fopen(sourcePath, "r");
    if(source == NULL) ERR(122, "Failed to create file '%s'.", sourcePath);

    char buffer[1000] = "";

    fgets(buffer, 1000, source);
    fputs(buffer, out); //column name

    if(descending) _writeInFileDescendingABR(out, head);
    else _writeInFileAscendingABR(out, head);

    fclose(out);
    fclose(source);
}