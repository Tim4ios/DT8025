/*
 * Part of the code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
 * Updated by Wagner Morais and Hazem Ali on 20/09/21.
 * Updated by Wagner Morais on Sept 22.
*/

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdarg.h>

#include "lib/tinythreads.h"
#include "lib/rpi3.h"
#include "lib/piface.h"
#include "lib/led.h"
#include "lib/expstruct.h"

#include "rpi-armtimer.h"
#include "lib/rpi-systimer.h"
#include "rpi-interrupts.h"

/** @brief Checks whether the input parameter is divisible by itself and 1, i.e, if the input parameter is prime.
 *  @param int i Is the input parameter to be checked whether it is prime or not
 *  @return int Returns 1 if the input parameter is prime, else it returns 0.
 * 
 *  Pre-condition: Input parameter i mus tbe positive
 * 
 *  test-cases: 
 *  is_prime(7) must return 1, i.e., true
 *  is_prime(9) must return 0, i.e., false
 *  is_prime(-1) must return 0, i.e., false
 */
int is_prime(int i) {
    // To be implemented!!!
    if (i <= 1) return 0;
    if (i % 2 == 0 && i > 2) return 0;
    for (int j = 3; j < i / 2; j += 2)
        if (i % j == 0)
            return 0;
    return 1;
}

/** @brief Toggle the state of the LED.
  * @param int seg Is the segment, i.e., 0: top left, 1:top right, 2: bottom left and 3: bottom right.
 */
void toggle_led(int seg) {
    while (1) {
        toggle();
        yield();
    }
}

void toggle_piface(int seg) {
    int col = 0;
    int row = 0;
    //If seg is 0 then 0,0, 1 then 1,0, 2 then 0,1, 3 then 1,1
    switch (seg) {
        case 1:
            col = 1;
            break;
        case 2:
            row = 1;
            break;
        case 3:
            col = 1;
            row = 1;
            break;
        default:
            break;
    }
    piface_set_cursor(col, row);

}

/** @brief For all positive integers, displays prime numbers in a given segment 
 *  @param int seg Is the segment, i.e., 0: top left, 1:top right, 2: bottom left and 3: bottom right.
 */
void computePrimes(int seg) {
    for (int n = 0;; n++) {
        if (is_prime(n)) {
            //PUTTOLDC("T%i: Prime %i\n", seg, n);
            print_at_seg(seg, n);
            RPI_WaitMicroSeconds(500000); //delay of 0.5s added for visualization purposes!!!
            yield();
        }
    }
}

/** @brief For all positive integers, displays the power of a given number
  * @param int seg Is the segment, i.e., 0: top left, 1:top right, 2: bottom left and 3: bottom right.
 */
void computePower(int seg) {
    for (int n = 0;; n++) {
        //PUTTOLDC("T%i: %i^2=%i\n", seg, n, n*n);
        print_at_seg(seg, n * n);
        RPI_WaitMicroSeconds(500000); //delay of 0.5s added for visualization purposes!!!
        yield();
    }
}

/** @brief Loops over the positive integers less than 21, 
  * calculates the exponential function and displays the integer part in a given segment.  
  * @param int seg Is the segment, i.e., 0: top left, 1:top right, 2: bottom left and 3: bottom right.
 */
void computeExponential(int seg) {
    //It will compute and display the result of the iexp function in a particular segment in the LED
    ExpStruct *value;
    int i;
    while (1) {

        for (i = 0; i < 21; ++i) {
            value = iexp(i);

            if (seg % 2) {
                print_at_seg(seg, value->expFraction);
                //sprintf(str,"%d: %d", i, value->expFraction);
            } else {
                print_at_seg(seg, value->expInt);
                // sprintf(str,"%d: %d", i, value->expInt);
            }

            RPI_WaitMicroSeconds(500000);
            free(value);
            yield();
        }
        piface_clear();
    }


}


int main() {
    led_init();
    piface_init();
    piface_clear();
    piface_puts("DT8025 - A3P3");
    RPI_WaitMicroSeconds(1000000);
    piface_clear();


    spawn(computePower, 0);
    spawn(computePrimes, 1);
    spawn(computeExponential, 2);
    spawn(computeExponential, 3);
    toggle_led(4);
}