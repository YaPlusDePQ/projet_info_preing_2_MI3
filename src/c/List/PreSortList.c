#include "../mainDefine.h"

int ChecksSortedAscending(List * plist){                //Returns 1 if it isn't sorted in ascending order, 0 if it is - checking the first element - for options 1,2,3 and wind
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem1 > p->next->elem1){                  //checks in a loop if it isn't ascended sorted
            return 1;                                   //Means it isn't sorted 
        }
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedDescending(List * plist){               //Returns 1 if it isn't sorted in descending order, 0 if it is - checking the first element - for options 1,2,3 and wind
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem1 < p->next->elem1){                  //checks in a loop if it isn't descended sorted
            return 1;                                   //Means it isn't sorted
        }               
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedAscending2(List * plist){               //Returns 1 if it isn't sorted in ascending order, 0 if it is - checking the second element - for height option
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem2 > p->next->elem2){                  //checks in a loop if it isn't ascended sorted
            return 1;                                   //Means it isn't sorted 
        }
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedDescending2(List * plist){              //Returns 1 if it isn't sorted in descending order, 0 if it is - checking the second element - for height option
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->elem2 < p->next->elem2){                  //checks in a loop if it isn't descended sorted
            return 1;                                   //Means it isn't sorted
        }               
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedAscendingMax(List * plist){             //Returns 1 if it isn't sorted in ascending order, 0 if it is - for the moisture option
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->max > p->next->max){                      //checks in a loop if it isn't ascended sorted
            return 1;                                   //Means it isn't sorted 
        }
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksSortedDescendingMax(List * plist){            //Returns 1 if it isn't sorted in descending order, 0 if it is - for the moisture option
    List * p = plist;
    while(p->next != NULL){                             //We stop there because we can't test p->next if p is NULL
        if(p->max < p->next->max){                      //checks in a loop if it isn't descended sorted
            return 1;                                   //Means it isn't sorted
        }               
        p = p->next;
    }
    return 0;                                           //Means it is sorted
}

int ChecksDoubleSortedAscending(List * plist){          //Returns 1 if the first row isn't sorted in ascending order and the second as well, return 0 if it is - for option 3
    List * p = plist;
    while(p->next != NULL){                             //Loop to go through the list
        if((p->elem1 == p->next->elem1) &&(p->elem2 > p->next->elem2)){     //Condition to see if it's sorted
            return 1;                                   //Means it's not sorted
        }                   
        p = p->next;
    }
    return 0;                                           //Means it's sorted
}

int ChecksDoubleSortedDescending(List * plist){         //Returns 1 if the first row isn't sorted in descending order and the second as well, return 0 if it is - for option 3
    List * p = plist;
    while(p->next != NULL){                             //Loop to go through the list
        if((p->elem1 == p->next->elem1) &&(p->elem2 < p->next->elem2)){
            return 1;                                   //Means it's not sorted
        }
        p = p->next;
    }
    return 0;                                           //Means it's sorted
}

    //to be able to sort with min, max and the average
List * PreCalculus(List * plist){                                   //Creates a list with every occurence of the first element to be able to do the calculus needed in PreSort
    List * tmp = ListCreation(plist->elem1,plist->elem2,0,0,0);     //Creates a temporary list 
    List * p = plist;
    int process = plist->elem1;                                     //We use process to compare after
    while(p->next != NULL){
        p = p->next;
        if(process == p->elem1){                                    //If it is the same element as the first we processed, then we add it to the temporary list 
            tmp = ListInsertEnd(tmp,p->elem1,p->elem2,0,0,0);       
        }
    }
    return tmp;
}

List * PreCalculusWind(List * plist){                               //Creates a list with every occurence of the first element to be able to do min_x and min_y in PreSortWind
    List * tmp = ListCreation(plist->elem1,plist->elem2,plist->elem3,0,0);      //Creates a temporary list 
    List * p = plist;
    int process = plist->elem1;
    while(p->next != NULL){
        p = p->next;
        if(process == p->elem1){                                                //If it is the same element as the first we processed, then we add it to the tmp list 
            tmp = ListInsertEnd(tmp,p->elem1,p->elem2,plist->elem3,0,0);
        }
    }
    return tmp;
}

List * PreSortMinMaxAv(List * plist){                               //Creates a list with every station with their minimun, maximum and average - for option 1
    List * final = ListCreation(plist->elem1,0,0,0,0);              //Creates the list we'll use to sort for min, max, average options
    List * tmp = PreCalculus(plist);                                //Gets the first tmp list
    int occur = occurence(plist,plist->elem1);
    plist = DeleteAllOccurences(plist,plist->elem1,occur);          //Deletes the values we processed, because they won't be needed anymore
    final->min = Min(tmp);                                          //fill the final list with tmp's calculus
    final->max = Max(tmp);
    final->average = Average(tmp);
    List * f = final;
    while(plist != NULL){                                           //Repeats the action for every tmp list
        final = ListInsertEnd(final,plist->elem1,0,0,0,0);
        f = f->next;
        List * tmp = PreCalculus(plist);                    
        occur = occurence(plist,plist->elem1);
        plist = DeleteAllOccurences(plist,plist->elem1,occur);      //Deletes plist's links when used, it's why it isn't an infinite loop
        f->min = Min(tmp);
        f->max = Max(tmp);
        f->average = Average(tmp);
        free(tmp);
    } 
    return final;
}

List * PreSortAv(List * plist){                                     //Creates a list with every date/hour for all stations with their average - for option 2
    List * final = ListCreation(plist->elem1,0,0,0,0);              //Creates the list we'll use to sort for average option
    List * tmp = PreCalculus(plist);                                //Gets the first tmp list
    int occur = occurence(plist,plist->elem1);
    plist = DeleteAllOccurences(plist,plist->elem1,occur);          //Deletes the values we processed, because they won't be needed anymore
    final->average = Average(tmp);                                  //fill the final list with tmp's calculus
    List * f = final;
    while(plist != NULL){                                           //Repeats the action for every tmp list
        final = ListInsertEnd(final,plist->elem1,0,0,0,0);
        f = f->next;
        List * tmp = PreCalculus(plist);                    
        occur = occurence(plist,plist->elem1);
        plist = DeleteAllOccurences(plist,plist->elem1,occur);      //Deletes plist's links when used, it's why it isn't an infinite loop
        f->average = Average(tmp);
        free(tmp);
    } 
    return final;
}

List * PreSortMax(List * plist){                                    //Creates a list with every station with their max moisture - for the moisture option
    List * final = ListCreation(plist->elem1,0,0,plist->lat,plist->lon);        //Creates the list we'll use to sort for min, max, average options
    List * tmp = PreCalculus(plist);                                            //Gets the first tmp list
    int occur = occurence(plist,plist->elem1);
    plist = DeleteAllOccurences(plist,plist->elem1,occur);                      //Deletes the values we processed, because they won't be needed anymore
    final->max = Max(tmp);                                                      //fill the final list with tmp's calculus
    List * f = final;
    while(plist != NULL){                                                       //Repeats the action for every tmp list
        final = ListInsertEnd(final,plist->elem1,0,0,plist->lat,plist->lon);
        f = f->next;
        List * tmp = PreCalculus(plist);                    
        occur = occurence(plist,plist->elem1);
        plist = DeleteAllOccurences(plist,plist->elem1,occur);                  //Deletes plist's links when used, it's why it isn't an infinite loop
        f->max = Max(tmp);
        free(tmp);
    } 
    return final;
}

List * PreSortWind(List * plist){                                   //Creates a list with every station with x's average ad y's average - for the wind option
    List * final = ListCreation(plist->elem1,0,0,plist->lat,plist->lon);        //Creates the list we'll use to sort for win_x,win_y
    List * tmp = PreCalculusWind(plist);                                        //Gets the first tmp list
    int occur = occurence(plist,plist->elem1);
    plist = DeleteAllOccurences(plist,plist->elem1,occur);                      //Deletes the values we processed, because they won't be needed anymore
    final->elem2 = Average(tmp);                                                //fill the final list with tmp's calculus
    final->elem3 = Average3(tmp);
    List * f = final;   
    while(plist != NULL){                                                       //Repeats the action for every tmp list
        final = ListInsertEnd(final,plist->elem1,0,0,plist->lat,plist->lon);
        f = f->next;
        List * tmp = PreCalculusWind(plist);                    
        occur = occurence(plist,plist->elem1);
        plist = DeleteAllOccurences(plist,plist->elem1,occur);                  //Deletes plist's links when used, it's why it isn't an infinite loop
        f->elem2 = Average(tmp);
        f->elem3 = Average3(tmp);
        free(tmp);
    } 
    return final;
}