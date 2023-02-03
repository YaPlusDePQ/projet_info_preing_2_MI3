#include "../mainDefine.h"

List * ListCreation(long long int a, float b, float c, int lat, int lon){                //To create a list with it's first link (including 3 rows, latitude, longitude)
    List * p = malloc(sizeof(List));                    //Creation with a malloc
    if (p == NULL){                                     //verification
        exit(1);
    }
    p->elem1 = a;                                       //Filling the list, its two elements 
    p->elem2 = b;
    p->elem3 = c;
    p->lat = lat;
    p->lon = lon;
    p->min = 0;
    p->max = 0;
    p->average = 0;
    p->next = NULL;                                     //Setting the next link it goes to to NULL
    return p;
}

List* ListInsertEnd(List * plist, long long int a, float b, float c, int lat, int lon){  //To insert a link (3 rows, latitude, longitude) to the list, at the end of it 
    List * new = ListCreation(a,b,c,lat,lon);
    List * p = plist;
    while(p->next != NULL){                             //Loop to go until the link is NULL to link it to a new one created above
        p = p->next;
    }
    p->next = new;                                      //Linking the new link
    return plist;
}

void DisplayList(List * plist){             //To display the list
    List * p = plist;
    while(p != NULL){                       //Loop to go until the end of the list
        if(p->next == NULL){
            printf("%lld; %f; %f; min : %d; max : %d; av : %f; lat : %d; lon : %d\n\n", p->elem1,p->elem2,p->elem3,p->min,p->max,p->average,p->lat,p->lon);
        }
        else{
            printf("%lld; %f; %f; min : %d; max : %d; av : %f; lat : %d; lon : %d   ->\n", p->elem1,p->elem2,p->elem3,p->min,p->max,p->average,p->lat,p->lon);
        }
        p = p->next;
    }
}

List * DeleteBeginning(List * plist){       //Deletes the first link of a list
    List *p = plist;
    if(plist != NULL){
        plist = p->next;                    //move the head of the list
        free(p);                            //free the first link 
    }
    return plist;
}

List * DeleteEnd(List * plist){             //Deletes the last link of a list
    List *p = plist;
    if(plist != NULL){
        while(p->next->next != NULL){       //loop to get to the end of the list
            p = p->next;
        } 
    }
    free(p->next);                          //free the last link
    p->next = NULL;                         //we need to set the next on NULL so that we don't end up with a value
    return plist;
}

List * DeleteMiddle(List * plist, int pos){ //Deletes a link in the list with it's position
    List *p = plist;
    List *p2;
    for(int i=0; i <pos-1;i++){             //Goes just before the link we want to delete
        p = p->next;
    }
    p2 = p->next;
    p->next = p2->next;
    free(p2);
    return plist;
}

List *  Del(List * plist, int sup){         //Deletes a link in a list no matter it's position
    List * p = plist;
    int compt = 0;
    if(plist == NULL){                      //Empty list case      
        exit(1);
    }

    while((p != NULL) &&(p->elem1 != sup)){ //loop to go through the whole list
        p = p->next;
        compt++;
    }

    if(p == NULL){                          //We reached the end so nothing to delete
        return plist;
    }

    if(p == plist){                         //Beginning of the list
        plist = DeleteBeginning(plist);
        return plist;
    }

    if(p->next == NULL){                    //End of the list
        plist = DeleteEnd(plist);
        return plist;
    }

    else{                                   //middle of the list
        plist = DeleteMiddle(plist,compt);
        return plist;
    }
}

int occurence(List * plist, int sup){       //Returns the number of times a value (first row) appears into the list
    int occur = 0;
    List * p = plist;
    while(p != NULL){
        if(p->elem1 == sup){
            occur++;
        }
        p = p->next;
    }
    return occur;
}

    //need the function occurence() above for the variable occur
List * DeleteAllOccurences(List * plist, int sup, int occur){   //Deletes all the occurences of a value (in the first) in a list , no matter if it's at the begginning, the middle or the end 
    List * p = plist;
    if(occur == 0){                                             //stopping condition - meaning we deleted all the occurrences
        return plist;
    }
    plist = Del(p,sup);                                         //calling del to delete one occurence
    plist = DeleteAllOccurences(plist,sup,occur-1);             //recursive call of the function to repeat
    return plist;
}
