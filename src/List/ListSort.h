#ifndef LISTSORT
#define LISTSORT
#include "../mainDefine.h"

List * SortOption1(List *plist);            //sorting the first row (Station ID) in ascending order

List * SortOption1Reverse(List *plist);     //sorting the first row (Station ID) in descending order

List * SortOption2(List *plist);            //sorting the first row (Date/hour) in ascending order

List * SortOption2Reverse(List *plist);     //sorting the first row (Date/hour) in descending order

List * SortOption3(List *plist);            //sorting the first row (Date/hour) and then the second (ID Station) in ascending order

List * SortOption3Reverse(List *plist);     //sorting the first row (Date/hour) and then the second (ID Station) in descending order

List * SortWind(List * plist);              //sorting the first row (Station ID) in ascendind order, elem2 is x's average and elem3 is y's average 

List * SortWindReverse(List *plist);        //sorting the first row (Station ID) in descending order, elem2 is x's average and elem3 is y's average 

List * SortHeight(List *plist);             //sorting the first row (Height) in descending order

List * SortHeightReverse(List *plist);      //sorting the first row (Height) in ascending order

List * SortMoisture(List *plist);           //sorting the first row (moisture) in descending order

List * SortMoistureReverse(List *plist);    //sorting the first row (moisture) in ascending order

#endif