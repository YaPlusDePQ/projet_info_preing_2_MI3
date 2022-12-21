#ifndef MAINDEFINE
#define MAINDEFINE

/* std library */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* optional library */
#include <stdbool.h>
#include <string.h>
// #include <math.h>
// #include <time.h>

/* debug define and macro */
#define DEBUG 1 //

#define DPRINTF(fmt, ...) if(DEBUG){printf(fmt __VA_OPT__(,) ##__VA_ARGS__);}
#define ERR(code, format, ...) do{printf("*********ERROR (%d): ", code);printf(format __VA_OPT__(,) ##__VA_ARGS__);exit(code);}while(0)

/* 
Error code:
1xx: allocation
    10x /ABR-AVL/node.c
    11x /ABR-AVL/dataFmtg.c
2xx: failed to read
    20x /ABR-AVL/node.c
    21x /ABR-AVL/dataFmtg.c



*/

/* headers */
#include "./ABR-AVL/node.h"
#include "./ABR-AVL/abr.h"
#include "./ABR-AVL/dataFmtg.h"

#endif