/*
    Part of the Raspberry-Pi Bare Metal Tutorials
    https://www.valvers.com/rpi/bare-metal/
    Copyright (c) 2013-2020, Brian Sidebotham

    This software is licensed under the MIT License.
    Please see the LICENSE file included with this software.
*/

/*
 * Part of the code below has been developed by Johan Nordlander and Fredrik Bengtsson at LTU.
 * Part of the code has been also developed, modified and extended to ARMv8 by Wagner de Morais and Hazem Ali.
*/
/*
 * Modified by Wagner Morais on Sep 2022.
*/


#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdarg.h>

#include "tinythreads.h"
#include "rpi3.h"
#include "piface.h"
#include "expstruct.h"

#include "rpi-armtimer.h"
#include "rpi-systimer.h"
#include "rpi-interrupts.h"

__attribute__(( always_inline )) static inline void enable_interrupts() {
  __asm volatile("cpsie i \n"); 
}

__attribute__(( always_inline )) static inline void disable_interrupts() {
  __asm volatile("cpsid i \n"); 
}

__attribute__(( always_inline )) static inline void no_operation() {
  __asm volatile("nop \n"); //AIF
}

#define DISABLE()       disable_interrupts()
#define ENABLE()        enable_interrupts()
#define MAXINT          0x7fffffff


// Mutex variable to guard critical sections
mutex mute = MUTEX_INIT;

// @brief The BCM2835 Interupt controller peripheral at it's base address
static rpi_irq_controller_t* rpiIRQController =
        (rpi_irq_controller_t*)RPI_INTERRUPT_CONTROLLER_BASE;

// @brief Return the IRQ Controller register set
static rpi_irq_controller_t* RPI_GetIrqController( void )
{
    return rpiIRQController;
}

void RPI_EnableARMTimerInterrupt(void)
{
    RPI_GetIrqController()->Enable_Basic_IRQs = RPI_BASIC_ARM_TIMER_IRQ;
}

void initTimerInterrupts()
{
    RPI_EnableARMTimerInterrupt();  
    /* Setup the system timer interrupt
       Timer frequency = Clk/256 * 0x400
       0xF3C is about 1 second       
	   0xF3C - 3900 - 9953 
    */
    RPI_GetArmTimer()->Load = 0xF3C;
    /* Setup the ARM Timer */
    RPI_GetArmTimer()->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;
    /* Enable interrupts! */
    ENABLE();
}

/** @brief Represents a job with an "infinite" execution time.
 */
void computeSomethingForever(int seg) {
    ExpStruct* value;
	for(volatile uint32_t i=0; ; i++)
    {
		// exp of the 1st 9 positive integers, except 0 
		value = iexp((i%8)+1);
		print_at_seg(seg % 4, value->expInt);
		// printf_at_seg(seg % 4, "S%i: %04i", seg, value->expInt);
    }
} 


/** @brief Represents a job with a fixed-length execution time.
 */
void computeSomething(int seg) {
	volatile int t = ticks;
	ExpStruct* value = iexp(10);
	printf_at_seg(seg % 4, "S%d: %d", seg, t);
	while(t==ticks);
} 

int main() {
	piface_init();
	piface_puts("DT8025 - A4P2");
	RPI_WaitMicroSeconds(2000000);	
	piface_clear();
    
	spawnWithDeadline(computeSomething, 0, 5, 5);
	spawnWithDeadline(computeSomething, 1, 3, 3);
    spawnWithDeadline(computeSomething, 2, 7, 7);

	initTimerInterrupts();
		
    while (1)
        no_operation();
}