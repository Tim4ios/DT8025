/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Wagner Morais on Aug 2022.
 */
 
#include "led.h"
#include "rpi3.h"
#include "rpi-systimer.h"
#include "rpi-gpio.h"

volatile unsigned int ledon = 0;

void led_init(){

	/* Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
       peripheral register to enable GPIO16 as an output */
    GPIO->GPFSEL1 |= (1 << 18);

// #if defined( RPI3 ) && defined( IOBPLUS )
	// RPI_SetGpioPinFunction( LED_GPIO, FS_OUTPUT );
// #endif	
}

void led_blink(){

}

void led_on(){
	/* Set the GPIO16 output high ( Turn OK LED off )*/
	GPIO->GPSET0 |= (1 << 16);
// #if defined( RPI3 ) && defined( IOBPLUS )	
	// /* Set the ACT LED attached to GPIO29 output high ( Turn OK LED off )
	   // Declarations in rpi-gpio.h
	// */
	// GPIO->LED_GPSET |= (1 << LED_GPIO_BIT);
// #endif		

}

void led_off(){
	/* Set the GPIO16 output high ( Turn OK LED off )*/
	GPIO->GPCLR0 |= (1 << 16);
// #if defined( RPI3 ) && defined( IOBPLUS )		
	// /* Set the ACT LED attached to GPIO29 output high ( Turn OK LED off )
	   // Declarations in rpi-gpio.h
	// */
	// GPIO->LED_GPCLR |= (1 << LED_GPIO_BIT);
// #endif	

}

void led_toggle() {

}