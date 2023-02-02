#include "mainDefine.h"

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

/**
*  \brief convert month in day.
*
*  \param month month of the year.
*
*  \return day.
*/
int monthToDay(int month){
    int day = 0;
    for(int i=1; i<month+1; i++){
        switch(i){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                day += 31;
                break;
            case 2:
                day += 28; //no leap year
                break;
            default:
                day += 30;
                break;
        }

    }
    return day;
}

/**  
*  \brief calculate date in seconds for easy sort.
*
*  \param date date format: YYYY-MM-DDTHH:00:00+UTC:00.
*
*  \return day.
*/
long long int dateToInt(const char* date){
    int year = -1;
    int month = -1;
    int day = -1;
    int hour = -1;
    int utc = -1;
    if(sscanf(date, "%d-%d-%dT%d:00:00+%d:00", &year, &month, &day, &hour, &utc) == 5){ //test if data get collected
        return ( (year*365+monthToDay(month)+day)*24 + hour + utc )*3600; //date in second. every year are 365 day for simplification (no impact detected)
    }
    else{
        //ERR(210, "Failed to read data from %s", date);
        printf("error\n\n");
    }
}
