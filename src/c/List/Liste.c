#include "mainDefine.h"

/*A faire :
-pour option 3, si la même date heure, trier par ID de station
- c écrit dans un fichier .dat avec séparateur ' ' - fait
*/

// ------------ BASE LIST FUNCTIONS ------------ 

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
}


// ------------ FILE ------------ 
List * FileIntoList2(FILE * file, int op){                      //gets the 2 rows into the list, the 2 rows are into one link - for options 1 (op=1) and option 2 (op=2)
    char v[100] = "", v1[100] = "", v2[100] = "";               //char that will get the second row
    long long int vv1;
    float vv2;
    int i=0,j=0;
    char first_line[100] = "";                                  //char to get the first line
    fgets(first_line,100,file);                                 //to remove the healine before putting in the list
    do{
    fscanf(file,"%s",v);                                        //gets the second line to create the list
    }while((strcmp(v,";") == 0));                               //if the line is empty we don't keep it
    while(v[i] != ';'){                                         //filling v1 and v2 in 2 loops
            v1[i] = v[i];
            i++;
    }
    i++;
    while(v[i] != '\0'){
        v2[j] = v[i];
        i++;
        j++;
    }
    if(op == 1){                                                //For the option 1
        vv1 = atoi(v1);                                         //converts the char into a int
    }
    else if(op == 2){                                           //For the option 2
        vv1 = dateToInt(v1);                                    //Converts the char into a long long int - (for Date/Hour)
    }
    vv2 = atoi(v2);
    List * plist = ListCreation(vv1,vv2,0,0,0);                 //Creation of the list with the values above
    while(!feof(file)){                                         //loop to fill the list with all the lines - same as the case of the second line
        if(file != NULL){                                       //verification
            char v[100] = "", v1[100] = "", v2[100] = "";  
            long long int vv1;                                  //char that will get the second row
            float vv2;
            int i=0,j=0;
            do{
                fscanf(file,"%s",v);                            //getting the two rows on the current line
            }while((strcmp(v,";") == 0));                       //if the line is empty we don't keep it   
            while(v[i] != ';'){                                 //filling v1 and v2 in 2 loops
                v1[i] = v[i];
                i++;
            }         
            i++;
            while(v[i] != '\0'){
                v2[j] = v[i];
                i++;
                j++;
            }
            if(op == 1){                                        //For the option 1
                vv1 = atoi(v1);                                 //Converts the char into a int
            }
            else if(op == 2){                                   //For the option 2
                vv1 = dateToInt(v1);                            //Converts the chat into a long long int - (for Date/Hour)
            }
            vv2 = atoi(v2);        
            plist = ListInsertEnd(plist,vv1,vv2,0,0,0);         //Putting each line from the third one in the list
        }
    }
    fclose(file);                                               //Closing the file                                      
    return plist;
}

List * FileIntoList3(FILE * file){                              //gets the 3 rows into the list, the 3 rows are into one link - for options 3
    char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "";
    float vv1,vv3;
    long long int vv2; 
    int i=0, j=0, k=0;
    char first_line[100] = "";             
    fgets(first_line,100,file);                                 //to remove the healine before putting in the list
    do{
    fscanf(file,"%s",v);                                        //gets the second line to create the list
    }while((strcmp(v,";;") == 0));                              //if the line is empty we don't keep it - meaning if v =';;'
    while(v[i] != ';'){                                         //Filling v1,v2 and v3 in 3 loops
            v1[i] = v[i];
            i++;
    }
    i++;
    while(v[i] != ';'){
        v2[j] = v[i];
        i++;
        j++;
    }
    i++;
    while(v[i] != '\0'){
        v3[k] = v[i];
        i++;
        k++;
    }
    vv1 = atoi(v1);                                             //Converts a char into a int 
    vv2 = dateToInt(v2);                                        //Convert a char into a long long int - (for Date/Hour)
    vv3 = atoi(v3);
    List * plist = ListCreation(vv2,vv1,vv3,0,0);

    while(!feof(file)){                                         //loop to fill the list with all the lines - same as the second line
        if(file != NULL){                                       //verification
            char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "";          
                float vv1,vv3;
                long long int vv2; 
                int i=0, j=0, k=0;
            do{
                fscanf(file,"%s",v);                            //getting the two rows on the current line
            }while((strcmp(v,";;") == 0));                      //if the line is empty we don't keep it   
            while(v[i] != ';'){
                v1[i] = v[i];
                i++;
            }
            i++;
            while(v[i] != ';'){
                v2[j] = v[i];
                i++;
                j++;
            }
            i++;
            while(v[i] != '\0'){
                v3[k] = v[i];
                i++;
                k++;
            }
            vv1 = atoi(v1);                                      //Converts a char into a int 
            vv2 = dateToInt(v2);                                 //Convert a char into a long long int - (for Date/Hour)
            vv3 = atoi(v3);    
            plist = ListInsertEnd(plist,vv2,vv1,vv3,0,0);        //Putting each line from the third (not empty) one in the list
        }
    }
    fclose(file);                                                //Closing the file            
    return plist;
}

List * FileIntoList4(FILE * file, int op){                      //gets the 4 rows into the list, the 4 rows are into one link - for the height (op=1) and moisture (op=2)
    List * plist;
    char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "", v4[100] = "";
    float vv2,vv4;
    long long int vv1; 
    int i=0, j=0, k=0,l=0, vv3=0; 
    char first_line[100] = "";             
    fgets(first_line,100,file);                     //to remove the healine before putting in the list
    do{
    fscanf(file,"%s",v);                            //gets the second line to create the list
    }while((strcmp(v,";;;") == 0));                 //if the line is empty we don't keep it - meaning if v =';;;'
    while(v[i] != ';'){                             //Fills v1,v2,v3 and v4 with 4 loops
            v1[i] = v[i];
            i++;
    }
    i++;
    while(v[i] != ';'){
        v2[j] = v[i];
        i++;
        j++;
    }
    i++;
    while(v[i] != ';'){
        v3[k] = v[i];
        i++;
        k++;
    }
    i++;
    while(v[i] != '\0'){
        v4[l] = v[i];
        i++;
        l++;
    }
    vv1 = atoi(v1);                                 //Converts a char into a int
    vv2 = atoi(v2);
    vv3 = atoi(v3);
    vv4 = atoi(v4);
    if(op == 1){                                    //For height 
        plist = ListCreation(vv1,vv4,0,vv2,vv3);    //Creation of the list and moving the rows of place
    }
    else if(op == 2){                               //For Moisture
        plist = ListCreation(vv1,vv2,0,vv3,vv4);    //Creation of the list
    }
    

    while(!feof(file)){                             //loop to fill the list with all the lines
        if(file != NULL){                           //verification
            char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "", v4[100] = "";         
                float vv2,vv4;
                long long int vv1; 
                int i=0, j=0, k=0,l=0, vv3=0; 
            do{
                fscanf(file,"%s",v);                //getting the two rows on the current line
            }while((strcmp(v,";;;") == 0));         //if the line is empty we don't keep it   
            while(v[i] != ';'){                     //Fills v1,v2,v3 and v4 with 4 loops
                v1[i] = v[i];           
                i++;
            }
            i++;
            while(v[i] != ';'){
                v2[j] = v[i];
                i++;
                j++;
            }
            i++;
            while(v[i] != ';'){
                v3[k] = v[i];
                i++;
                k++;
            }
            i++;
            while(v[i] != '\0'){
                v4[l] = v[i];
                i++;
                l++;
            }
            vv1 = atoi(v1);                         //Converts a char into a int
            vv1 = atoi(v1);                             
            vv2 = atoi(v2);    
            vv3 = atoi(v3); 
            vv4 = atoi(v4);
            if(op == 1){                            //For Height
                plist = ListInsertEnd(plist,vv1,vv4,0,vv2,vv3);         //Putting each line from the third (not empty) one in the list
            }
            else if(op == 2){                       //For Moisture
                plist = ListInsertEnd(plist,vv1,vv2,0,vv3,vv4);         //Putting each line from the third (not empty) one in the list
            }   
            
        }
    }
    fclose(file);                                   //Closing the file                                     
    return plist;
}

List * FileIntoList5(FILE * file){                              //gets the 5 rows into the list, the 5 rows are into one link - for the wind
    char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "", v4[100] = "",v5[100] = "";                                   
    long long int vv1;
    float vv2,vv3;
    int vv4, vv5,i=0, j=0, k=0, l=0,m=0;
    char first_line[100] = "";             
    fgets(first_line,100,file);                                 //to remove the healine before putting in the list
    do{
    fscanf(file,"%s",v);                                        //gets the second line to create the list
    }while((strcmp(v,";;;;") == 0));                            //if the line is empty we don't keep it - meaning if v =';;;;'
    while(v[i] != ';'){                                         //Fills v1,v2,v3,v4 and v5 with 5 loops
            v1[i] = v[i];
            i++;
    }
    i++;
    while(v[i] != ';'){
        v2[j] = v[i];
        i++;
        j++;
    }
    i++;
    while(v[i] != ';'){
        v3[k] = v[i];
        i++;
        k++;
    }
    i++;
    while(v[i] != ';'){
        v4[l] = v[i];
        i++;
        l++;
    }
    i++;
    while(v[i] != '\0'){
        v5[m] = v[i];
        i++;
        m++;
    }
    vv1 = atoi(v1);                                             //Converts a char into a int
    vv2 = atoi(v2);
    vv3 = atof(v3);
    vv4 = atoi(v4);
    vv5 = atoi(v5);
    List * plist = ListCreation(vv1,vv2,vv3,vv4,vv5);           //Creation of the list

    while(!feof(file)){                                         //loop to fill the list with all the lines
        if(file != NULL){                                       //verification
            char v[100] = "", v1[100] = "", v2[100] = "", v3[100] = "", v4[100] = "",v5[100] = "";          
            long long int vv1;
            float vv2,vv3;
            int vv4, vv5,i=0, j=0, k=0, l=0,m=0;
            do{
                fscanf(file,"%s",v);                            //getting the two rows on the current line
            }while((strcmp(v,";;;;") == 0));                    //if the line is empty we don't keep it   
            while(v[i] != ';'){                                 //Fills v1,v2,v3,v4 and v5 with 5 loops
                v1[i] = v[i];
                i++;
            }
            i++;
            while(v[i] != ';'){
                v2[j] = v[i];
                i++;
                j++;
            }
            i++;
            while(v[i] != ';'){
                v3[k] = v[i];
                i++;
                k++;
            }
            i++;
            while(v[i] != ';'){
                v4[l] = v[i];
                i++;
                l++;
            }
            i++;
            while(v[i] != '\0'){
                v5[m] = v[i];
                i++;
                m++;
            }
            vv1 = atoi(v1);                                     //Converts a char into a int
            vv2 = atoi(v2);    
            vv3 = atof(v3); 
            vv4 = atoi(v4);   
            vv5 = atoi(v5);
            plist = ListInsertEnd(plist,vv1,vv2,vv3,vv4,vv5);   //Putting each line from the third (not empty) one in the list
        }
    }
    fclose(file);                                               //Closing the file                                     
    return plist;
}

FILE* ListIntoFile(List * plist,int option){                    //puts the wanted rows into a .dat file - for every option
    FILE * end = NULL;
    end = fopen("cst char * name_file.dat","w");                //opening the returning file (have to put the path)
    if(end == NULL){                                            //verification
        printf("error from output file\n");
        printf("error code = %d \n",errno);
        printf("error message = %s \n",strerror(errno));
        exit(3);
    }
    List * p = plist;
    while(p != NULL){                                           //loop on each link of the list to fill the returning file
        switch(option){
            case 1 :                                    
                fprintf(end,"%lld;%d;%d;%f\n",p->elem1,p->min,p->max,p->average);               //puts the first row, the min,max and average into the file - for option 1
            case 2 :
                fprintf(end,"%lld;%f\n",p->elem1,p->average);                                   //puts the first row and the average into the file - for option 2
            case 3 :
                fprintf(end,"%lld;%f;%f\n",p->elem1,p->elem2,p->elem3);                         //puts the three rows into the file - for option 3 
            case 4 :
                fprintf(end,"%lld;%f;%f;%d;%d\n",p->elem1,p->elem2,p->elem3,p->lat,p->lon);     //puts the three rows, the latitude and longitude into the file - for option wind
            case 5 :
                fprintf(end,"%lld;%f;%d;%d\n",p->elem1,p->elem2,p->lat,p->lon);                 //puts the two rows, the latitude and longitude into the file - for option height
            case 6 :
                fprintf(end,"%lld;%d;%d;%d\n",p->elem1,p->max,p->lat,p->lon);                   //puts the first row, the average, the latitude and longitude into the file - for the option moisture
        }
        p = p->next;
    }
    //fclose(end);                                        //Don't know if I do it there ?
    return end;                                     
}


// ------------ CALCULUS ------------

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

float wind_x(List * plist){                                     //Calculates the average of the x - for the wind
    List * p = plist;
    float x=0,avx=0;
    int compt=0;
    while(p != NULL){                                           //Creates x sum with calculus into a loop
        x += (cos(p->elem2))*(p->elem3);
        compt++;
        p=p->next;
    }
    avx = x / compt;                                            //Calculus of x's average
    return avx;
}

float wind_y(List * plist){                                     //Calculates the x average of the y - for the wind
    List * p = plist;
    float y=0,avy=0;
    int compt=0;
    while(p != NULL){                                           //Creates y sum with calculus into a loop
        y += (sin(p->elem2))*(p->elem3);
        compt++;
        p=p->next;
    }
    avy = y / compt;                                            //Calculus of y's average
    return avy;
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
        ERR(210, "Failed to read data from %s", date);
        printf("error\n\n");
    }
}


// ------------ SORTING ------------ 

    //to check if a list is sorted in a specific order

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
    final->elem2 = wind_x(tmp);                                                 //fill the final list with tmp's calculus
    final->elem3 = wind_y(tmp);
    List * f = final;   
    while(plist != NULL){                                                       //Repeats the action for every tmp list
        final = ListInsertEnd(final,plist->elem1,0,0,plist->lat,plist->lon);
        f = f->next;
        List * tmp = PreCalculusWind(plist);                    
        occur = occurence(plist,plist->elem1);
        plist = DeleteAllOccurences(plist,plist->elem1,occur);                  //Deletes plist's links when used, it's why it isn't an infinite loop
        f->elem2 = wind_x(tmp);
        f->elem3 = wind_y(tmp);
        free(tmp);
    } 
    return final;
} 

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
    printf("testtest\n");
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
