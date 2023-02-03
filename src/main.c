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

    switch(mode[1]){
        case 'm':
            if(!strcmp(type, "--abr")) HeightMoistureModeABRAVL(sourcePath, outPath, MOISTUREMODE, 0, !isReversed);
            if(!strcmp(type, "--avl")) HeightMoistureModeABRAVL(sourcePath, outPath, MOISTUREMODE, 1, !isReversed);
            else Moisture(sourcePath, outPath,isReversed);
            break;
        case 'h':
            if(!strcmp(type, "--abr"))HeightMoistureModeABRAVL(sourcePath, outPath, HEIGHTMODE, 0, !isReversed);
            if(!strcmp(type, "--avl"))HeightMoistureModeABRAVL(sourcePath, outPath, HEIGHTMODE, 1, !isReversed);
            else Height(sourcePath, outPath, isReversed);
            break;
        case 'w':
            if(!strcmp(type, "--abr"))WindModeABRAVL(sourcePath, outPath, 0, isReversed);
            if(!strcmp(type, "--avl"))WindModeABRAVL(sourcePath, outPath, 1, isReversed);
            else Wind(sourcePath, outPath, isReversed);
            break;
        case 't':
        case 'p':
            switch(mode[2]){
                case '1':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, outPath, 0, 1, isReversed);
                    if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, outPath, 1, 1, isReversed);
                    else Option1(sourcePath, outPath, isReversed);
                    break;
                case '2':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, outPath, 0, 2, isReversed);
                    if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, outPath, 1, 2, isReversed);
                    else Option2(sourcePath, outPath, isReversed);
                    break;
                case '3':
                    if(!strcmp(type, "--abr"))TempPressureModeABRAVL(sourcePath, outPath, 0, 3, isReversed);
                    if(!strcmp(type, "--avl"))TempPressureModeABRAVL(sourcePath, outPath, 1, 3, isReversed);
                    else Option3(sourcePath, outPath, isReversed);
                    break;
            }
            break;
    }
    return 0;
}