/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "expstruct.h"

int fac(int a) //function to find factorial
{
    if (a == 0 || a == 1)
        return 1;
    int f = 1;
    for (int w = 0; w < a; ++w) {
        f *= (a - w);
    }
    return f;
}

ExpStruct *iexp(int x) {
    ExpStruct *e = malloc(sizeof(ExpStruct));

    int k = 0;
    double h, g = 0;
    do {
        e->expInt += ((x ^ (k)) / (fac(k)));
        e->expFraction += (int) modf(g, &h);
        k++;

    }
    while(k < 22);



    return e;


}
