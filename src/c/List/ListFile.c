#include "../mainDefine.h"

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
    if(strlen(v1)==0 || strlen(v2)==0){   //To remove half-filled lines after
        vv1 = -9999;                                //Sets the values like that to delete them after
        vv2 = -9999;
    }
    else{
        vv2 = atoi(v2);                                    //Convert a char into a long long int - (for Date/Hour)
        if(op == 1){                                            //For the option 1 
            vv1 = atoi(v1);                                     //converts the char into a int
        }
        else if(op == 2){                                       //For the option 2
            vv1 = dateToInt(v1);                                //Converts the char into a long long int - (for Date/Hour)
        }
    }
    
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
            if(strlen(v1)==0 || strlen(v2)==0){                 //To remove half-filled lines after
                vv1 = -9999;                                    //Sets the values like that to delete them after
                vv2 = -9999;
            }
            else{
                if(op == 1){                                    //For the option 1 
                    vv1 = atoi(v1);                             //converts the char into a int
                }
                else if(op == 2){                               //For the option 2
                    vv1 = dateToInt(v1);                        //Converts the char into a long long int - (for Date/Hour)
                }
                vv2 = atoi(v2);                                 //Convert a char into a long long int - (for Date/Hour)
            }      
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
    if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0){        //To remove half-filled lines after
        vv1 = -9999;                                            //Sets the values like that to delete them after
        vv2 = -9999;
        vv3 = -9999;
    }
    else{
        vv1 = atoi(v1);                                         //Converts a char into a int
        vv2 = dateToInt(v2);                                    //Convert a char into a long long int - (for Date/Hour)
        vv3 = atoi(v3);
    }
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
            if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0){        //To remove half-filled lines after
                vv1 = -9999;                                            //Sets the values like that to delete them after
                vv2 = -9999;
                vv3 = -9999;
            }
            else{
                vv1 = atoi(v1);                                         //Converts a char into a int
                vv2 = dateToInt(v2);                                    //Convert a char into a long long int - (for Date/Hour)
                vv3 = atoi(v3);
            }   
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
    if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0 || strlen(v4)==0){   //To remove half-filled lines after
        vv1 = -9999;                                //Sets the values like that to delete them after
        vv2 = -9999;
        vv3 = -9999;
        vv4 = -9999;
    }
    else{
        vv1 = atoi(v1);                              //Converts a char into a int
        vv2 = atoi(v2);
        vv3 = atoi(v3);
        vv4 = atoi(v4);
    }
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
            if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0 || strlen(v4)==0){   //To remove half-filled lines after
                vv1 = -9999;                          //Sets the values like that to delete them after
                vv2 = -9999;
                vv3 = -9999;
                vv4 = -9999;
            }
            else{
                vv1 = atoi(v1);                      //Converts a char into a int
                vv2 = atoi(v2);
                vv3 = atoi(v3);
                vv4 = atoi(v4);
            }
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
    if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0 || strlen(v4)==0 || strlen(v5)==0){   //To remove half-filled lines after
        vv1 = -9999;                          //Sets the values like that to delete them after
        vv2 = -9999;
        vv3 = -9999;
        vv4 = -9999;
        vv5 = -9999;
    }
    else{
        vv1 = atoi(v1);                      //Converts a char into a int
        vv2 = atoi(v2);
        vv3 = atoi(v3);
        vv4 = atoi(v4);
        vv5 = atoi(v5);
    }
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
            if(strlen(v1)==0 || strlen(v2)==0 || strlen(v3)==0 || strlen(v4)==0 || strlen(v5)==0){   //To remove half-filled lines after
                vv1 = -9999;                         //Sets the values like that to delete them after
                vv2 = -9999;
                vv3 = -9999;
                vv4 = -9999;
                vv5 = -9999;
            }
            else{
                vv1 = atoi(v1);                      //Converts a char into a int
                vv2 = atoi(v2);
                vv3 = atoi(v3);
                vv4 = atoi(v4);
                vv5 = atoi(v5);
            }              
            plist = ListInsertEnd(plist,vv1,vv2,vv3,vv4,vv5);   //Putting each line from the third (not empty) one in the list
        }
    }
    fclose(file);                                               //Closing the file                                     
    return plist;
}

FILE* ListIntoFile(List * plist,FILE * end,int option){                    //puts the wanted rows into a .dat file - for every option except option 3
    List * p = plist;
    while(p->next != NULL){                                           //loop on each link of the list to fill the returning file
        switch(option){
            case 1 :                                    
                fprintf(end,"%I64d;%d;%d;%f\n",p->elem1,p->min,p->max,p->average);               //puts the first row, the min,max and average into the file - for option 1
                break;
            case 2 :
                fprintf(end,"%I64d;%f\n",p->elem1,p->average);                                   //puts the first row and the average into the file - for option 2
                break;
            case 4 :
                fprintf(end,"%I64d;%f;%f;%d;%d\n",p->elem1,p->elem2,p->elem3,p->lat,p->lon);     //puts the three rows, the latitude and longitude into the file - for option wind
                break;
            case 5 :
                fprintf(end,"%I64d;%f;%d;%d\n",p->elem1,p->elem2,p->lat,p->lon);                 //puts the two rows, the latitude and longitude into the file - for option height
                break;
            case 6 :
                fprintf(end,"%I64d;%d;%d;%d\n",p->elem1,p->max,p->lat,p->lon);                   //puts the first row, the average, the latitude and longitude into the file - for the option moisture
                break;
            default : 
                printf("error");
                break;
        }

        p = p->next;
    }                                       
    return end;                                     
}

FILE * ListIntoFile2(List * plist, FILE * end){         //puts the wanted rows into a .dat file - for option 3
    List * p = plist;
    while(p->next != NULL){
        if(p->elem1 != p->next->elem1){
            fprintf(end,"%I64d;%f;%f\n\n\n",p->elem1,p->elem2,p->elem3);                      //puts the three rows into the file - for option 3 
        }
        else{
            fprintf(end,"%I64d;%f;%f\n",p->elem1,p->elem2,p->elem3);                         //puts the three rows into the file - for option 3 
        }
        p = p->next;
    }
    fprintf(end,"%I64d;%f;%f\n",p->elem1,p->elem2,p->elem3);                                 //puts the three rows into the file - for option 3 
}


