#ifndef MAINDEFINE
#define MAINDEFINE

/* std library */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* optional library */
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <math.h>
// #include <time.h>

/* debug define and macro */
#define DEBUG 0 //

#define MAX(a,b) (a > b ? a : b)

#define DPRINTF(fmt, ...) if(DEBUG){printf(fmt __VA_OPT__(,) ##__VA_ARGS__);}
#define ERR(code, format, ...) do{printf("*********ERROR (%d): ", code);printf(format __VA_OPT__(,) ##__VA_ARGS__);exit(code);}while(0)

/* 
Error code:
1xx: allocation
    10x /ABR-AVL/node.c
    11x /ABR-AVL/dataFmtg.c
    12x /ABR-AVL/abr.c
2xx: failed to read
    20x /ABR-AVL/node.c
    21x /ABR-AVL/dataFmtg.c
    22x /ABR-AVL/abr.c
3xx: failed to write
    30x /ABR-AVL/abr.c
*/

/* headers */
#include "./ABR-AVL/tool.h"
#include "./ABR-AVL/heightMoisture.h"
#include "./ABR-AVL/tempPressure.h"
#include "./ABR-AVL/wind.h"
#include "./List/List.h"

#endif