#include "../mainDefine.h"

// ------------ BASE LIST FUNCTIONS ------------ 

List * ListCreation(int a, int b){                     //To create a list with it's first link (including 2 elements)
    List * p = malloc(sizeof(List));
    if (p == NULL){
        exit(1);
    }
    p->elem1 = a;
    p->elem2 = b;
    p->next = NULL;
    return p;
}

List* ListInsert(List * plist, int a, int b){          //To insert a link (2 numbers) to the list, at the end of it 
    List * new = ListCreation(a,b);
    List * p = plist;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = new;
    return plist;
}

void DisplayList(List * plist){                        //To display the list
    List * p = plist;
    while(p != NULL){
        if(p->next == NULL){
            printf("%d;%d \n", p->elem1,p->elem2);
        }
        else{
            printf("%d;%d -> ", p->elem1,p->elem2);
        }
        p = p->next;
    }
}

// ------------ FILE ------------ 
List * FileIntoList(FILE * file){                       //gets the 2 rows into the list, the 2 rows are into one link
    int v1 = 0;
    int v2 = 0;
    char first_line[100] = "";               
    fgets(first_line,100,file);                         //to remove the healine before putting in the list
    fscanf(file,"%d;%d",&v1,&v2);                       //gets the second line to create the list
    List * plist = ListCreation(v1,v2);
    while(!feof(file)){                                 //loop to fill the list with all the lines
        if(file != NULL){
            fscanf(file,"%d;%d",&v1,&v2);
            if(!feof(file)){
                plist = ListInsert(plist,v1,v2);        //Putting each line from the third in the list
            }
        }
    }
    fclose(file);
    return plist;
}

FILE* ListIntoFile(List * plist){
    FILE * end = NULL;
    end = fopen("chemin_du_fichier","r+");              //opening the returning file (have to put the path)
    if(end == NULL){                                    //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
    List * p = plist;
    while(p != NULL){                                    //loop on each link of the list
        fprintf(end,"%d;%d\n",p->elem1,p->elem2);        //filling the returning file
        p = p->next;
    }
    fclose(end);                                        //Don't know if I do it there 
    return end;                                     
}
// ------------ SORTING ------------ 

List * SortAscending(List *plist){                      //sorting the first row in ascending order
    List * tmp, * p;
    int  swap1,swap2; 
    if(plist != NULL){
        for(tmp = plist;tmp->next != NULL;tmp = tmp->next){
            for(p = tmp->next;p != NULL;p = p->next){
                if(p->elem1 < tmp->elem1){
                    swap1 = p->elem1;
                    swap2 = p->elem2;
                    p->elem1 = tmp->elem1;
                    p->elem2 = tmp->elem2;
                    tmp->elem1 = swap1;
                    tmp->elem2 = swap2;
                }
            }
        }
    }
    return plist;
}

List * SortDescending(List *plist){                     //sorting the first row in descending order
    List * tmp, * p;
    int  swap1,swap2; 
    if(plist != NULL){
        for(tmp = plist;tmp->next != NULL;tmp = tmp->next){
            for(p = tmp->next;p != NULL;p = p->next){
                if(p->elem1 > tmp->elem1){
                    swap1 = p->elem1;
                    swap2 = p->elem2;
                    p->elem1 = tmp->elem1;
                    p->elem2 = tmp->elem2;
                    tmp->elem1 = swap1;
                    tmp->elem2 = swap2;
                }
            }
        }
    }
    return plist;
}
