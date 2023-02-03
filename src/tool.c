#include "mainDefine.h"

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
            //ugly but work
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
        return ( (year*365+monthToDay(month)+day)*24 + hour + utc ); //date in second. every year are 365 day for simplification (no impact detected)
    }
    else{
        exit(1);//ERR(210, "Failed to read date from %s", date);
    }
}
