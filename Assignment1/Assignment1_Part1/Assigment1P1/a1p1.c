/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>
#include "uart.h"
#include "iregister.h"

#define LINE 80


int main() {
    iRegister r;
    char str[LINE];
    int inumber, inibble, ibit, ishift, nibblepos = 0;


    uart_init();
    uart_clear();

    uart_welcome(str);

    resetAll(&r);
    uart_puts("Enter a integer (32 bit) : ");
    uart_setBits(str);
    inumber = atoi(str);
    print2uart("You entered number: %d ", inumber);
    r.content = inumber;
    char *a = reg2str(r);
    print2uart("\n");
    print2uart("Integer returned in binary      ");
    uart_puts(a);
    print2uart("\n");


    uart_puts("Enter the bit position (0<=bit<=31) : ");
    uart_setBits(str);
    ibit = atoi(str);


    uart_puts("Enter the nibble position (0 <= nibble <=7) : ");
    uart_setBits(str);
    inibble = atoi(str);


    uart_puts("Enter the nibble value (0 <= nibble <=15) : ");
    uart_setBits(str);
    nibblepos = atoi(str);

    uart_puts("Enter the number of bits to shift (1<=bits<=31) : ");
    uart_setBits(str);
    ishift = atoi(str);
    print2uart("Shift: %d", ishift);
    print2uart(" Bit: %d", ibit);
    print2uart(" Nibble: %d", inibble);
    print2uart(" NibblePos: %d", inibble);
    print2uart("\n");

    setAll(&r);
    char *g = reg2str(r);
    print2uart("setAll(&r) returned %d          ", r.content);
    uart_puts(g);
    print2uart("\n");

    resetAll(&r);
    char *f = reg2str(r);
    print2uart("resetAll(&r) returned %d         ", r.content);
    uart_puts(f);
    print2uart("\n");


    r.content = inumber;
    setBit(ibit, &r);
    char *m = reg2str(r);
    print2uart("setBit(&r) returned %d          ", r.content);
    uart_puts(m);
    print2uart("\n");


    print2uart("getBit(&r) returned %d          ", getBit(ibit, &r));
    print2uart("\n");


    resetBit(ibit, &r);
    char *h = reg2str(r);
    print2uart("resetBit(&r) returned %d        ", r.content);
    uart_puts(h);
    print2uart("\n");


    assignNibble(inibble, nibblepos, &r);
    char *l = reg2str(r);
    print2uart("assignNibble(&r) returned %d   ", r.content);
    uart_puts(l);
    print2uart("\n");


    getNibble(inibble, &r);
    char *k = reg2str(r);
    print2uart("getNibble(&r) returned %d        ", getNibble(inibble, &r));
    uart_puts(k);
    print2uart("\n");

    shiftRight(ishift, &r);
    char *j = reg2str(r);
    print2uart("shiftRight(&r) returned %d      ", r.content);
    uart_puts(j);
    print2uart("\n");

    shiftLeft(ishift, &r);
    char *t = reg2str(r);
    print2uart("shiftLeft(&r) returned %d      ", r.content);
    uart_puts(t);
    print2uart("\n");




    // To Display a string
    // uart_puts("String\n");
    // To get one character
    // c=uart_getc();

    // To get a number, you might want to call uart_getc multiple times until receiving a new line.
    // The results of each call to uart_getc can be stored into str
    // atoi(str) will result a number.
    return 0;
}


