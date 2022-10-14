/*
 * Copyright (C) 2018 bzt (bztsrc@github)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
/*
 * Modified by Wagner Morais on Sep 20 2021.
 */

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "rpi-base.h"
#include "rpi-gpio.h"


/* Auxilary mini UART registers */
#define AUX_ENABLE		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215004))
#define AUX_MU_IO		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215040))
#define AUX_MU_IER		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215044))
#define AUX_MU_IIR		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215048))
#define AUX_MU_LCR		((volatile unsigned int * )(PERIPHERAL_BASE + 0x0021504C))
#define AUX_MU_MCR		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215050))
#define AUX_MU_LSR		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215054))
#define AUX_MU_MSR		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215058))
#define AUX_MU_SCRATCH	((volatile unsigned int * )(PERIPHERAL_BASE + 0x0021505C))
#define AUX_MU_CNTL		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215060))
#define AUX_MU_STAT		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215064))
#define AUX_MU_BAUD		((volatile unsigned int * )(PERIPHERAL_BASE + 0x00215068))

/**
 *set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void uart_init() {
    register unsigned int r;

    /* initialize UART */
    *AUX_ENABLE |= 1; // enable UART1, AUX mini uart
    *AUX_MU_CNTL = 0;
    *AUX_MU_LCR = 3; // 8 bits
    *AUX_MU_MCR = 0;
    *AUX_MU_IER = 0;
    *AUX_MU_IIR = 0xc6; // disable interrupts	000000000000000000000000 11 00 0 11 0
    *AUX_MU_BAUD = 270; // 115200 baud
    /* map UART1 to GPIO pins */
    r = RPI_GetGpio() -> GPFSEL0;
    r &= ~((7 << 12) | (7 << 15)); // gpio14, gpio15
    r |= (2 << 12) | (2 << 15); // alt5
    RPI_GetGpio() -> GPFSEL1 = r;
    RPI_GetGpio() -> GPPUD = 0; // enable pins 14 and 15
    r = 150;
    while (r--) {
        asm volatile("nop");
    }
    RPI_GetGpio() -> GPPUDCLK0 = (1 << 14) | (1 << 15);
    r = 150;
    while (r--) {
        asm volatile("nop");
    }
    RPI_GetGpio() -> GPPUDCLK0 = 0; // flush GPIO setup
    *AUX_MU_CNTL = 3; // enable Tx, Rx
}

/**
 *send a character
 */
void uart_send(unsigned int c) {
    /* wait until we can send */
    do {
        asm volatile("nop");
    } while (!( *AUX_MU_LSR & 0x20));
    /* write the character to the buffer */
    *AUX_MU_IO = c;
}

/**
 * Receive a character
 */
char uart_getc() {
    char r;
    /* wait until something is in the buffer */
    do {
        asm volatile("nop");
    } while (!( *AUX_MU_LSR & 0x01));
    /* read it and return */
    r = (char)( *AUX_MU_IO);
    /* convert carriage return to newline */
    return r == '\r' ? '\n' : r;
}

/**
 * Display a string
 */
void uart_puts(char *s) {
    while ( *s) {
        /* convert newline to carriage return + newline */
        if ( *s == '\n')
            uart_send('\r');
        uart_send( *s++);
    }
}

void uart_clear() {
    uart_send(0x1B);
    uart_send(0x5B);
    uart_send(0x32);
    uart_send(0x4A);
}

void print2uart(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[vsnprintf(NULL, 0, fmt, args) + 1];
    va_end(args);
    va_start(args, fmt);
    vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);
    uart_puts(buf);
}