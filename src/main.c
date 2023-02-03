#include "mainDefine.h"

//main --[abr/avl/tab] -f [...] -o [...] -[tx/px/m/h/w] -r
int main(int argc, char **argv){
    
    char type[6] = "";
    char sourcePath[1000] = "";
    char outPath[1000]= "";
    char mode[3] = "";
    int isReversed=0;

    strcpy(type,argv[1]);
    strcpy(sourcePath, argv[3]);
    strcpy(outPath, argv[5]);
    strcpy(mode, argv[6]);
    isReversed = argc==7;
    printf("[main] starting sorting...\n");
    switch(mode[1]){
        case 'm':
            if(!strcmp(type, "--abr")) HeightMoistureModeABRAVL(sourcePath, "../output/moisturesorted.csv", MOISTUREMODE, 0, !isReversed);
            else{ 
                if(!strcmp(type, "--avl")) HeightMoistureModeABRAVL(sourcePath, "../output/moisturesorted.csv", MOISTUREMODE, 1, !isReversed);
                else Moisture(sourcePath, "../output/moisturesorted.csv",isReversed);
            }
            break;
        case 'h':
            if(!strcmp(type, "--abr"))HeightMoistureModeABRAVL(sourcePath, outPath, "../output/heightsorted.csv", 0, !isReversed);
            else {
                if(!strcmp(type, "--avl"))HeightMoistureModeABRAVL(sourcePath, outPath, "../output/heightsorted.csv", 1, !isReversed);
                else Height(sourcePath, "../output/heightsorted.csv", isReversed);
            }
            break;
        case 'w':
            if(!strcmp(type, "--abr"))WindModeABRAVL(sourcePath, "../output/windsorted.csv", 0, isReversed);
            else {
                if(!strcmp(type, "--avl"))WindModeABRAVL(sourcePath, "../output/windsorted.csv", 1, isReversed);
                else Wind(sourcePath, outPath, isReversed);
            }
            break;
        case 't':
            switch(mode[2]){
                case '1':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/temperature1sorted.csv", 0, 1, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/temperature1sorted.csv", 1, 1, isReversed);
                        else Option1(sourcePath, "../output/temperature1sorted.csv", isReversed);
                    }
                    break;
                case '2':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/temperature2sorted.csv", 0, 2, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/temperature2sorted.csv", 1, 2, isReversed);
                        else Option2(sourcePath, "../output/temperature2sorted.csv", isReversed);
                    }
                    break;
                case '3':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/temperature3sorted.csv", 0, 3, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/temperature3sorted.csv", 1, 3, isReversed);
                        else Option3(sourcePath, "../output/temperature3sorted.csv", isReversed);
                    }
                    break;
            }
            break;
        case 'p':
            switch(mode[2]){
                case '1':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/pression1sorted.csv", 0, 1, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/pression1sorted.csv", 1, 1, isReversed);
                        else Option1(sourcePath, "../output/pression1sorted.csv", isReversed);
                    }
                    break;
                case '2':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/pression2sorted.csv", 0, 2, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/pression2sorted.csv", 1, 2, isReversed);
                        else Option2(sourcePath, "../output/pression2sorted.csv", isReversed);
                    }
                    break;
                case '3':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, "../output/pression3sorted.csv", 0, 3, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, "../output/pression3sorted.csv", 1, 3, isReversed);
                        else Option3(sourcePath, "../output/pression3sorted.csv", isReversed);
                    }
                    break;
            }
            break;
    }
    printf("[main] Done\n");
    return 0;
}