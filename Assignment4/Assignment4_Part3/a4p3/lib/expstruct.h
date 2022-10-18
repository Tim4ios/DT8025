/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
 */
/*
 * Modified by Wagner Morais on Aug 2022.
 */

#ifndef _EXPSTRUCT_H
#define _EXPSTRUCT_H

#include <stdint.h>

struct expStruct {
    int expInt;
    int expFraction;
};

typedef struct expStruct ExpStruct;

/** @brief Calculates the Taylor expansion of e^x with an accuracy of 2 decimals, sets the integer and fraction in the expStruct
 *
 *  @param x is the integer value which appears as x in the equation for the expansion
 *
 *  @return e, a pointer to an expStruct structure containing 2 integer values
 *
 *  Pre-condition: Check if x is positive or zero, if not return NULL
 *
 *  Post-condition: Check if memory was allocated if not return NULL
 *
 *  Properties:
 *  Example: iex(1) -> calculates e^1 sets expInt to the left side of the decimal point
 *  then sets expFraction to the remainder of the difference between double and integer multiplies that by 100.
 *  By multiplying it by 100 and casting it to an int you get 2 decimal precision
 */
ExpStruct *iexp(int x);

#endif