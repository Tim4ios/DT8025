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

ExpStruct *iexp(int x){
	ExpStruct *e = malloc(sizeof(ExpStruct));
    int i = 0;
    int g = 0;
    int n = 21;
    unsigned long long fact = 1;

    for (i = 0; i <= n; ++i) {
        e->expFraction *= i;
        e->expInt = i;
        e = (x^i) /  e->expFraction;
    }


	return e;	
}
