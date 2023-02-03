#include "../mainDefine.h"

int Min(List * plist){                                          //Takes a second list with only one station and all it's values to fin the minimum (int the 1st row) 
    List * p = plist;
    int min = p->elem2;                                                        //We need the minimum of the temperature or pression, so it is second raw
    while(p->next != NULL){
        if((p->elem2 <= p->next->elem2) && (p->elem2 < min)){                  //1st condition to compare and take the smallest number
            min = p->elem2;
        }
        else if((p->next->elem2 <= p->elem2) && (p->next->elem2 < min)){       //2nd condition to compare and take the smallest number
            min = p->next->elem2;
        }
        p = p->next;
    }
    return min;
}

int Max(List * plist){                                          //Takes a second list with only one station and all it's values to fin the maximum (in the 1st row)
    List * p = plist;
    int max = p->elem2;                                                        //We need the minimum of the temperature or pression, so it is second raw
    while(p->next != NULL){
        if((p->elem2 >= p->next->elem2) && (p->elem2 > max)){                  //1st condition to compare and take the biggest number
            max = p->elem2;
        }
        else if((p->next->elem2 >= p->elem2) && (p->next->elem2 > max)){       //2nd condition to compare and take the biggest number
            max = p->next->elem2;
        }
        p = p->next;
    }
    return max;
}

float Average(List * plist){                                    //Takes a second list with only one station and all it's values to fin the average (in the 1st row)
    List * p = plist;
    int sum = 0, compt = 0;
    float moy=0;
    while(p != NULL){                                           //loop to go through the list
        sum += p->elem2;
        compt++;
        p = p->next;
    }
    moy = sum / compt;                                          //To calcul the average 
    return moy;
}

float Average3(List * plist){                                   //Takes a second list with only one station and all it's values to fin the average (in the 3rd row)
    List * p = plist;
    int sum = 0, compt = 0;
    float moy=0;
    while(p != NULL){                                           //loop to go through the list
        sum += p->elem3;
        compt++;
        p = p->next;
    }
    moy = sum / compt;                                          //To calcul the average 
    return moy;
}
