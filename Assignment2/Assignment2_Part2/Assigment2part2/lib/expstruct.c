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
#include "expstruct.h"
#include "piface.h"

double fac(int a) //function to find factorial
{
    if (a == 0 || a == 1)
        return 1;
    double f = 1;
    for (int w = 0; w < a; ++w) {
        f *= (a - w);
    }
    return f;
}

double ppow(int base, int exp)
{
    double result = 1;

    for (exp; exp>0; exp--)
    {
        result = result * base;
    }
    return result;

}

ExpStruct *iexp(int x) {
    ExpStruct *e = malloc(sizeof(ExpStruct));
    double h = 0;
    int f;
    int y;
    double g;
    for (int i = 0; i < 22; i++) {
        h = h + ppow(x, i) / (fac(i));
        e->expInt = h;
        g = (h - e->expInt) * 100;
        f = g;
        e->expFraction = f + e->expFraction;
    }

    return e;

}

