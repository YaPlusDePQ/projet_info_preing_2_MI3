#include "mainDefine.h"
    
    
    //For temperatures and pressions

        //Option 1
List * SortOption1(List *plist){                        //sorting the first row (Station ID) in ascending order
    List * p = plist;
    List * tmp = plist->next;
    long long int swap1=0; 
    int swapMax=0,swapMin=0,swapAv=0;
    while(ChecksSortedAscending(plist)){                //Calls a function that checks if the list is sorted as we want
        if(p->elem1 > tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swapMax = p->max;
            swapMin = p->min;
            swapAv = p->average;

            p->elem1 = tmp->elem1;
            p->max = tmp->max;
            p->min = tmp->min;
            p->average = tmp->average;

            tmp->elem1 = swap1;
            tmp->max = swapMax;
            tmp->min = swapMin;
            tmp->average = swapAv;
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

List * SortOption1Reverse(List *plist){                 //sorting the first row (Station ID) in descending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0;
    int swapMax=0,swapMin=0,swapAv=0;
    while(ChecksSortedDescending(plist)){               //Calls a function that checks if the list is sorted as we want
        if(p->elem1 < tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swapMax = p->max;
            swapMin = p->min;
            swapAv = p->average;

            p->elem1 = tmp->elem1;
            p->max = tmp->max;
            p->min = tmp->min;
            p->average = tmp->average;

            tmp->elem1 = swap1;
            tmp->max = swapMax;
            tmp->min = swapMin;
            tmp->average = swapAv;
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

        //Option 2
List * SortOption2(List *plist){                        //sorting the first row (Date/hour) in ascending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1;
    int swapAv=0;
    while(ChecksSortedAscending(plist)){                //Calls a function that checks if the list is sorted as we want
        if(p->elem1 > tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swapAv = p->average;

            p->elem1 = tmp->elem1;
            p->average = tmp->average;

            tmp->elem1 = swap1;
            tmp->average = swapAv;
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

List * SortOption2Reverse(List *plist){                 //sorting the first row (Date/hour) in descending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1;
    int swapAv=0;
    while(ChecksSortedDescending(plist)){               //Calls a function that checks if the list is sorted as we want
        if(p->elem1 < tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swapAv = p->average;

            p->elem1 = tmp->elem1;
            p->average = tmp->average;

            tmp->elem1 = swap1;
            tmp->average = swapAv;
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

        //Option 3
List * SortOption3(List *plist){                        //sorting the first row (Date/hour) and then the second (ID Station) in ascending order
    List * p = plist;
    List * tmp = plist->next;
    long long int swap1=0; 
    float swap2=0; 
    int swap3=0;
    while(ChecksSortedAscending(plist)){                //Calls a function that checks if the list is sorted as we want - first we sort the first row
        if(p->elem1 > tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;

            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;

            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
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
    p = plist;
    tmp = plist->next;
    DisplayList(plist);
    while(ChecksDoubleSortedAscending(plist)){
        if((p->elem1 == p->next->elem1) && (p->elem2 > p->next->elem2)){
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;

            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;

            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
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

List * SortOption3Reverse(List *plist){                 //sorting the first row (Date/hour) and then the second row(ID Station) in descending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0; 
    float swap2=0;
    int swap3=0;
    while(ChecksSortedDescending(plist)){                //Calls a function that checks if the list is sorted as we want - first we sort the first row
        if(p->elem1 < tmp->elem1){                      //Tests if the elements need to be swapped, meaning if the first one is bigger than the second
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;

            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;

            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
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
    p = plist;
    tmp = plist->next;
    while(ChecksDoubleSortedDescending(plist)){
        if((p->elem1 == p->next->elem1) && (p->elem2 < p->next->elem2)){
            swap1 = p->elem1;                           //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;

            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;

            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
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


    //For the wind
List * SortWind(List * plist){                         //sorting the first row (Station ID) in ascendind order, elem2 is x's average and elem3 is y's average 
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0;
    int swaplat=0,swaplon=0;
    float swap2=0,swap3=0;
    while(ChecksSortedAscending(plist)){               //Call a function that checks if the list is sorted as we want
        if(p->elem1 > tmp->elem1){                     //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;
            swaplat = p->lat;
            swaplon = p->lon;
            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;
            p->lat = tmp->lat;
            p->lon = tmp->lon;
            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
            tmp->lat = swaplat;
            tmp->lon = swaplon;
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}

List * SortWindReverse(List *plist){                   //sorting the first row (Station ID) in descending order, elem2 is x's average and elem3 is y's average 
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0;
    int swaplat=0,swaplon=0;
    float swap2=0,swap3=0;
    while(ChecksSortedDescending(plist)){              //Call a function that checks if the list is sorted as we want
        if(p->elem1 < tmp->elem1){                     //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swap3 = p->elem3;
            swaplat = p->lat;
            swaplon = p->lon;
            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->elem3 = tmp->elem3;
            p->lat = tmp->lat;
            p->lon = tmp->lon;
            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->elem3 = swap3;
            tmp->lat = swaplat;
            tmp->lon = swaplon;
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}


    //For the height - It has to be sorted in descending order 

List * SortHeight(List *plist){                        //sorting the second row (Height) in descending order 
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0; 
    float swap2=0;
    int swaplat=0,swaplon=0;
    while(ChecksSortedDescending2(plist)){             //Call a function that checks if the list is sorted as we want
        if(p->elem2 < tmp->elem2){                     //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swaplat = p->lat;
            swaplon = p->lon;

            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->lat = tmp->lat;
            p->lon = tmp->lon;

            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->lat = swaplat;
            tmp->lon = swaplon;
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}

List * SortHeightReverse(List *plist){                 //sorting the second row (Height) in ascending order 
    List * p = plist;
    List * tmp = plist->next;
    long long int swap1=0; 
    float swap2=0;
    int swaplat=0,swaplon=0;
    while(ChecksSortedAscending2(plist)){              //Call a function that checks if the list is sorted as we want
        if(p->elem2 > tmp->elem2){                     //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swap2 = p->elem2;
            swaplat = p->lat;
            swaplon = p->lon;
            p->elem1 = tmp->elem1;
            p->elem2 = tmp->elem2;
            p->lat = tmp->lat;
            p->lon = tmp->lon;
            tmp->elem1 = swap1;
            tmp->elem2 = swap2;
            tmp->lat = swaplat;
            tmp->lon = swaplon;
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}


    //For the moisture - It has to be sorted in descending order

List * SortMoisture(List *plist){                      //sorting the second row (moisture's max per station) in descending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0;
    int swapMax=0,swaplat,swaplon;
    while(ChecksSortedDescendingMax(plist)){           //Call a function that checks if the list is sorted as we want
        if(p->max < tmp->max){                         //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swapMax = p->max;                            
            swaplat = p->lat;
            swaplon = p->lon;

            p->elem1 = tmp->elem1;
            p->max = tmp->max;
            p->lat = tmp->lat;
            p->lon = tmp->lon;

            tmp->elem1 = swap1;
            tmp->max = swapMax;
            tmp->lat = swaplat;
            tmp->lon = swaplon;            
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}

List * SortMoistureReverse(List *plist){               //sorting the second row (moisture's max per station) in ascending order
    List * p = plist;
    List * tmp = plist->next; 
    long long int swap1=0;
    int swapmax=0,swaplat=0,swaplon=0;
    while(ChecksSortedAscendingMax(plist)){            //Call a function that checks if the list is sorted as we want
        if(p->max > tmp->max){                         //Tests if the elements need to be swapped, meaning if the first one is smaller than the second
            swap1 = p->elem1;                          //Swapping of the elements with intermediate variables
            swapmax = p->max;                            
            swaplat = p->lat;
            swaplon = p->lon;

            p->elem1 = tmp->elem1;
            p->max = tmp->max;
            p->lat = tmp->lat;
            p->lon = tmp->lon;

            tmp->elem1 = swap1;
            tmp->max = swapmax;
            tmp->lat = swaplat;
            tmp->lon = swaplon;  
        }
        if(tmp->next == NULL){                         //if we're at the end of the list, we go back to the beginning
            p = plist;
            tmp = p->next;
        }
        else{                                          //else we keep going further into the list
            p = p->next;
            tmp = tmp->next;
        }
    }
    return plist;
}