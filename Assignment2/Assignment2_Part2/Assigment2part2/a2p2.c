/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include "stdlib.h"
#include "expstruct.h"
#include "piface.h"


int main() {
    char *str = malloc(32 * sizeof(char));
    piface_init();
    piface_clear();

    piface_puts("DT8025 - A2P2");
    RPI_WaitMicroSeconds(20000);
    piface_clear();
    ExpStruct *value;
    while(1) {
        for (int i = 1; i < 21; ++i) {
            value = iexp(i);
            piface_clear();
            sprintf(str, "%d: %d.%d", i, value->expInt, value->expFraction);
            piface_puts(str);
            free(value);
        }
        piface_clear();
    }

    return 0;

}