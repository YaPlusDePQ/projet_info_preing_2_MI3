#ifndef PRESORTLIST
#define PRESORTLIST

#include "../mainDefine.h"

int ChecksSortedAscending(List * plist);        //Returns 1 if it isn't sorted in ascending order, 0 if it is - checking the first element - for options 1,2,3 and wind

int ChecksSortedDescending(List * plist);       //Returns 1 if it isn't sorted in descending order, 0 if it is - checking the first element - for options 1,2,3 and wind

int ChecksSortedAscending2(List * plist);       //Returns 1 if it isn't sorted in ascending order, 0 if it is - checking the second element - for height option

int ChecksSortedDescending2(List * plist);      //Returns 1 if it isn't sorted in descending order, 0 if it is - checking the second element - for height option

int ChecksSortedAscendingMax(List * plist);     //Returns 1 if it isn't sorted in ascending order, 0 if it is - for the moisture option

int ChecksSortedDescendingMax(List * plist);    //Returns 1 if it isn't sorted in descending order, 0 if it is - for the moisture option

int ChecksDoubleSortedAscending(List * plist);  //Returns 1 if the first row isn't sorted in ascending order and the second as well, return 0 if it is - for option 3

int ChecksDoubleSortedDescending(List * plist); //Returns 1 if the first row isn't sorted in descending order and the second as well, return 0 if it is - for option 3

List * PreCalculus(List * plist);           //Creates a list with every occurence of the first element to be able to do the calculus needed in PreSort

List * PreCalculusWind(List * plist);       //Creates a list with every occurence of the first element to be able to do min_x and min_y in PreSortWind

List * PreSortMinMaxAv(List * plist);       //Creates a list with every station with their minimun, maximum and average - for option 1

List * PreSortAv(List * plist);             //Creates a list with every date/hour for all stations with their average - for option 2

List * PreSortMax(List * plist);            //Creates a list with every station with their max moisture - for moisture option

List * PreSortWind(List * plist);           //Creates a list with every station with x's average ad y's average- for wind option

#endif