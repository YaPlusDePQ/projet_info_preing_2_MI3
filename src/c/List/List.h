#ifndef LIST
#define LIST

// ------------ STRUCTURE ------------ 

typedef struct list{
    long long int elem1;
    float elem2;
    float elem3;
    int min;
    int max;
    int lon;
    int lat;
    float average;
    struct list * next;
}List;


// ------------ BASE LIST FUNCTIONS ------------ 

List * ListCreation(long long int a, float b, float c, int lat, int lon);                              //To create a list with it's first link (including 3 rows, latitude, longitude)

List* ListInsertEnd(List * plist, long long int a,float b, float c, int lat, int lon);                 //To insert a link (3 rows, latitude, longitude) to the list, at the end of it 

void DisplayList(List * plist);                                 //To display the list

List * DeleteBeginning(List * plist);                           //Deletes the first link in a list

List * DeleteEnd(List * plist);                                 //Deletes the last link in a list

List * DeleteMiddle(List * plist, int pos);                     //Deletes a link in the middle of the list

List *  Del(List * plist, int sup);                             //Deletes a link in a list no matter it's position

int occurence(List * plist, int sup);                           //Returns the number of times a value (first row) appears into the list

List * DeleteAllOccurences(List * pliste, int sup, int occur);  //Deletes all the occurences of a value (in the first) in a list , no matter if it's at the begginning, the middle or the end 


// ------------ FILE ------------ 

List * FileIntoList2(FILE * file, int op);              //gets the 2 rows into the list, the 2 rows are into one link - for options 1 (op=1) and option 2 (op=2)

List * FileIntoList3(FILE * file);                      //gets the 3 rows into the list, the 3 rows are into one link - for options 3

List * FileIntoList4(FILE * file, int op);              //gets the 4 rows into the list, the 4 rows are into one link - for the height (op=1) and moisture (op=2)

List * FileIntoList5(FILE * file);                      //gets the 5 rows into the list, the 5 rows are into one link - for the wind

FILE* ListIntoFile(List * plist, int option);           //puts the wanted rows into a .dat file - for every option


// ------------ CALCULUS ------------

int Min(List * plist);                      //Takes a second list with only one station and all it's values to fin the minimum (in the 1st row)

int Max(List * plist);                      //Takes a second list with only one station and all it's values to fin the maximum (in the 1st row)

float Average(List * plist);                //Takes a second list with only one station and all it's values to fin the average (in the 1st row)

float wind_x(List * plist);                 //Calculates the average of x - for the wind 

float wind_y(List * plist);                 //Calculates the average of y - for the wind

int monthToDay(int month);                  //Converts months into days

long long int dateToInt(const char* date);  //Converts a date in this format "YYYY-MM-DDTHH:00:00+UTC:00" into a long long int


// ------------ SORTING ------------ 

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