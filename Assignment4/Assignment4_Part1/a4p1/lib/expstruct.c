/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#include <stdlib.h>
#include "expstruct.h"


//function to calculate a!
double fac(int a)
{
    if (a == 0 || a == 1)
        return 1;
    double f = 1;
    for (int w = 0; w < a; ++w) {
        f *= (a - w);
    }
    return f;
}

//To calculate base^exp
double ppow(int base, int exp) {
    double result = 1;

    for (exp; exp > 0; exp--) {
        result = result * base;
    }
    return result;
}

ExpStruct *iexp(int x) {
    //Pre-condition
    if(x<0){
       // fprint("Error: A NULL pointer was given\n");
        return NULL;
    }

    ExpStruct *e = malloc(sizeof(ExpStruct));

    if(e==NULL){
        //  fprintf("Error: Malloc failed to allocate memory\n");
        return NULL;
    }

    int two_dec_pre = 1;
    int counter = 0;
    double temp = 0;
    double memory = 0;

    while(two_dec_pre){
        temp += ppow(x,counter)/fac(counter);
        counter++;

        if(memory!= 0 && (temp-memory)<0.001) two_dec_pre = 0;

        memory = temp;
    }

    e->expInt = temp;
    e->expFraction = (temp - (int)temp)*100;

    return e;
}

