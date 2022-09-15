/*
	Modified by Wagner Morais on Sep 2022.
 */

#include <stdio.h>
#include "piface.h"
//#include "led.h"

int main() {


    piface_init();
    piface_clear();
    piface_puts("DT8025 - A2P1");
    while (1) {
        piface_clear();
        piface_puts("1st line\n2st line");
        piface_clear();
        piface_puts("Short string");
        piface_clear();
        piface_puts("This is a long string");
        piface_clear();
    }


    return 0;
}