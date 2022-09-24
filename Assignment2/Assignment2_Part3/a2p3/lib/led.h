/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Wagner Morais on Aug 2022.
 */
#ifndef LED_H
#define LED_H

// Similar to rpi-gpio.h
#define LEDHH_GPFSEL      GPFSEL1
#define LEDHH_GPFBIT      18
#define LEDHH_GPSET       GPSET0
#define LEDHH_GPCLR       GPCLR0
#define LEDHH_GPIO_BIT    16
#define LEDHH_GPIO        16

#define LEDHH_ON()        do { RPI_GetGpio()->LEDHH_GPSET = ( 1 << LEDHH_GPIO_BIT ); } while( 0 )
#define LEDHH_OFF()       do { RPI_GetGpio()->LEDHH_GPCLR = ( 1 << LEDHH_GPIO_BIT ); } while( 0 )


/** @brief Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO peripheral register to enable GPIO16 as an output
 *  @return void
 */

void led_init();

/** @breaf Set output pin to high
 * @return void
 */
void led_on();

/** @breaf Set output pin to low
 * @return void
 */
void led_off();

/** @breaf Set output pin to high and then low after a delay
 * @return void
 */
void led_blink();


#endif
