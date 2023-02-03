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

/* 
Error code:
1xx: allocation
    10x /ABR-AVL/heightMoisture.c
    11x /ABR-AVL/tempPressure1.c
    12x /ABR-AVL/tempPressure23.c
    13x /ABR-AVL/wind.h
2xx: failed to read
    20x /ABR-AVL/heightMoisture.c
    21x /ABR-AVL/tempPressure1.c
    22x /ABR-AVL/tempPressure23.c
    23x /ABR-AVL/wind.h
3xx: failed to write
    30x /ABR-AVL/heightMoisture.c
    31x /ABR-AVL/tempPressure1.c
    32x /ABR-AVL/tempPressure23.c
    33x /ABR-AVL/wind.h
*/

/* headers */
#include "tool.h"
#include "./ABR-AVL/heightMoisture.h"
#include "./ABR-AVL/tempPressure.h"
#include "./ABR-AVL/wind.h"

#include "./TAB/windL.h"
#include "./TAB/heightMoistureL.h"
#include "./TAB/tempPressureL.h"

// #include "./List/ListBaseFunction.h"
// #include "./List/ListCalculus.h"
// #include "./List/PreSortList.h"
// #include "./List/ListSort.h"
// #include "./List/ListFile.h"
// #include "./List/ListOptions.h"

#endif