#include "../mainDefine.h"

// ------------ BASE LIST FUNCTIONS ------------ 

List * ListCreation(int a, int b){                      //To create a list with it's first link (including 2 elements)
    List * p = malloc(sizeof(List));                     //Creation with a malloc
    if (p == NULL){                                      //verification
        exit(1);
    }
    p->elem1 = a;                                       //Filling the list, its two elements 
    p->elem2 = b;
    p->next = NULL;                                     //Setting the next link it goes to to NULL
    return p;
}

List* ListInsertEnd(List * plist, int a, int b){        //To insert a link (2 numbers) to the list, at the end of it 
    List * new = ListCreation(a,b);
    List * p = plist;
    while(p->next != NULL){                             //Loop to go until the link is NULL to link it to a new one created above
        p = p->next;
    }
    p->next = new;                                      //Linking the new link
    return plist;
}

void DisplayList(List * plist){                         //To display the list
    List * p = plist;
    while(p != NULL){                                  //Loop to go until the end of the list
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
        if(file != NULL){                               //verification
            fscanf(file,"%d;%d",&v1,&v2);               //getting the two rows one the current line
            if(!feof(file)){                            //testing if we are at the end of the file to insert, to avoid a double last line into the list
                plist = ListInsertEnd(plist,v1,v2);     //Putting each line from the third in the list
            }
        }
    }
    fclose(file);                                       
    return plist;
}

FILE* ListIntoFile(List * plist){
    FILE * end = NULL;
    end = fopen("cst char * name_file","w");            //opening the returning file (have to put the path)
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
    fclose(end);                                        //Don't know if I do it there ?
    return end;                                     
}
// ------------ SORTING ------------ 

int ChecksSortedAscending(List * plist){                //Returns 1 if it isn't sorted in ascending order, 0 if it is
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem1 > p->next->elem1){                  //checks in a loop if it isn't ascended sorted
            return 1;                                   //Means it isn't sorted 
        }
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedDescending(List * plist){               //Returns 1 if it isn't sorted in descending order, 0 if it is
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem1 < p->next->elem1){                  //checks in a loop if it isn't descended sorted
            return 1;                                   //Means it isn't sorted
        }               
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

List * SortAscending(List *plist){                      //sorting the first row in ascending order
    List * p = plist;
    List * tmp = plist->next; 
    int swap1=0,swap2=0;
    while(ChecksSortedAscending(plist)){                //Calls a function that checks if the list is sorted as we want
        if(p->elem1 > tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
        }
        if(tmp->next == NULL){                          //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                           //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}

List * SortDescending(List *plist){                     //sorting the first row in descending order
    List * p = plist;
    List * tmp = plist->next; 
    int swap1=0,swap2=0;
    while(ChecksSortedDescending(plist)){               //Call a function that checks if the list is sorted as we want
        if(p->elem1 < tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
        }
        if(tmp->next == NULL){                          //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                           //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}

