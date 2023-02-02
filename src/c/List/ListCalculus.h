#ifndef LISTCALCULUS
#define LISTCALCULUS

#include "../mainDefine.h"

int Min(List * plist);                      //Takes a second list with only one station and all it's values to fin the minimum (in the 1st row)

int Max(List * plist);                      //Takes a second list with only one station and all it's values to fin the maximum (in the 1st row)

float Average(List * plist);                //

float Average3(List * plist);               //Takes a second list with only one station and all it's values to fin the average (in the 3rd row)

int monthToDay(int month);                  //Converts months into days

long long int dateToInt(const char* date);  //Converts a date in this format "YYYY-MM-DDTHH:00:00+UTC:00" into a long long int


#endif