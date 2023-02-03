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
            if(!strcmp(type, "--abr")) HeightMoistureMode_ABRAVL(sourcePath, "../output/moisturesorted.csv", MOISTUREMODE, 0, !isReversed);
            else{ 
                if(!strcmp(type, "--avl")) HeightMoistureMode_ABRAVL(sourcePath, "../output/moisturesorted.csv", MOISTUREMODE, 1, !isReversed);
                else HeightMoistureMode_TAB(sourcePath, "../output/moisturesorted.csv",MOISTUREMODE, isReversed);
            }
            break;
        case 'h':
            if(!strcmp(type, "--abr"))HeightMoistureMode_ABRAVL(sourcePath, "../output/heightsorted.csv", HEIGHTMODE,0, !isReversed);
            else {
                if(!strcmp(type, "--avl"))HeightMoistureMode_ABRAVL(sourcePath, "../output/heightsorted.csv", HEIGHTMODE, 1, !isReversed);
                else HeightMoistureMode_TAB(sourcePath, "../output/heightsorted.csv",HEIGHTMODE, isReversed);
            }
            break;
        case 'w':
            if(!strcmp(type, "--abr"))WindMode_ABRAVL(sourcePath, "../output/windsorted.csv", 0, isReversed);
            else {
                if(!strcmp(type, "--avl"))WindMode_ABRAVL(sourcePath, "../output/windsorted.csv", 1, isReversed);
                else WindModeTAB(sourcePath, outPath, isReversed);
            }
            break;
        case 't':
            switch(mode[2]){
                case '1':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature1sorted.csv", 0, 1, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature1sorted.csv", 1, 1, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/temperature1sorted.csv", 1, isReversed);
                    }
                    break;
                case '2':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature2sorted.csv", 0, 2, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature2sorted.csv", 1, 2, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/temperature2sorted.csv", 2, isReversed);
                    }
                    break;
                case '3':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature3sorted.csv", 0, 3, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/temperature3sorted.csv", 1, 3, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/temperature3sorted.csv", 3, isReversed);
                    }
                    break;
            }
            break;
        case 'p':
            switch(mode[2]){
                case '1':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/pression1sorted.csv", 0, 1, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/pression1sorted.csv", 1, 1, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/pression1sorted.csv", 1, isReversed);
                    }
                    break;
                case '2':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/pression2sorted.csv", 0, 2, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/pression2sorted.csv", 1, 2, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/pression2sorted.csv", 2, isReversed);
                    }
                    break;
                case '3':
                    if(!strcmp(type, "--abr"))TempPressureMode_ABRAVL(sourcePath, "../output/pression3sorted.csv", 0, 3, isReversed);
                    else {
                        if(!strcmp(type, "--avl"))TempPressureMode_ABRAVL(sourcePath, "../output/pression3sorted.csv", 1, 3, isReversed);
                        else TempPressureMode_TAB(sourcePath, "../output/pression3sorted.csv", 3, isReversed);
                    }
                    break;
            }
            break;
    }
    printf("[main] Done\n");
    return 0;
}