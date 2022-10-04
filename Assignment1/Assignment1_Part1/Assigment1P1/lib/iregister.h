//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.
//  Last Modified 13/9 - 2022 by Joel Pålsson & Johan Elfing (group 4)

#ifndef lab0_iregister_h
#define lab0_iregister_h

/**
 *  iRegister
 *  An iRegister is a structure which represents an 32-bit register and
 *  is equipped with standard operations to modify and display them.
 */
typedef struct {
  int content;
} iRegister;

/**
 *  Bellow you find the declarations for the functions to modify and display the
 *  memory content of a iRegister data structure. Before each declaration, a
 * brief description about what the function shall do is given. Later in this
 * file, the documentation for the resetBit function is given. Students should
 * follow that format.
 */

/**@brief resets all the bits of the iRegister (to 0)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: iRegister != Null
 *
 * Post-condition r->content = 0
 *
 * Properties:
 * After setBit(r), getBit(i) = 0 if 0 <= i < 32 
 */
void resetAll(iRegister *);

/** sets the i'th bit of the iRegister (to 1)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 *  Post-condition: after set(i, r) the i'th bit of iRegister is 1, all other
 *  bits remain unchanged
 *
 *  properties:
 *  after setBit(i, r),  setBit(i, r) = 1
 *  if getBit(i, r) == 1 then
 *    getBit(j, r) returns the same value for all
 *  0 <= j < 32 and j <> i before and after setBit(i, r)
 */
void setBit(int, iRegister *);

/* @bief sets all the bits of the iRegister (to 1)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: iRegister != Null
 *
 * Post-condition r->content = 0xFFFFFFFF
 *
 * Properties:
 * After setBit(r), getBit(i) = 1 if 0 <= i < 32 
 */
void setAll(iRegister *);

/** @brief Returns the i'th bit of the iRegister as an integer (1 if it is set, or 0)
 *
 * @param i index where to retrive value of bit in iRegister r
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 * otherwise)
 *
 * @return int
 *
 * Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 * Properties: 
 * After setbit(i,r), getbit(i,r)=1. After resetbit(i,r), getbit(i,r)=0. Works the same for all 32 bits in iRegister r
 *
 */
int getBit(int, iRegister *);

/** @brief set nibble(four bits) at index(starting at 0) i to value y
 *
 * @param i index where to change nibble 
 *
 * @param y value to set nibble equal to
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return void
 *
 * Pre-condition: r != NULL, 0 <= y <=15 and 0 <= i <= 7
 *
 * Post-condition: getNibble(i,r) == y
 *
 * Properties:
 * after assignNibble(i, y, r), getNibble(i, r) = y
 *
 */
void assignNibble(int, int, iRegister *);

/** @brief get the nibble(4 bits in a row) at index i in iRegister
 *
 * @param i index where to retrieve nibble(four bits) inside iRegister
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return int
 *
 * Pre-condition: iRegister != NULL and  0 < i < 8 
 * 
 * Properties:
 * If int y = getNibble(i,r), y equals to nibble at index i. If i or r are invalid y = -1
 */
int getNibble(int, iRegister *);

/** @brief returns a pointer to an array of 32 characters, with each character
 *  representing the corresponding bit of the iRegister, i.e., if the bit is
 * set, then the character is "1" (ASCII char with code 49), or otherwise is "0"
 *  (ASCII char with code 48)
 *
 * @param r A pointer to a memory location of a iRegister data structure.
 *
 * @return char*
 *
 * Pre-condition: iRegister != Null & Check if malloc was successfull
 *
 * Properties:
 * After reg2str(r) printReg(reg2str) prints an char array where the LSB is in index 0 
 */
char *reg2str(iRegister);

/** @brief shifts all the bits of the iRegister to the right by n palces (appends
 * 0 from the left)
 *
 *  @param i Is the number of steps the contense in th register is to be shifted to
 * the right
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  
 *  Post-condition: Check if everything added through shifting is equal to zero
 *
 *  Properties:
 *  after shiftRight(i, r), r equal to r >> i
 */
void shiftRight(int, iRegister *);

/** @brief shifts all the bits of the iRegister to the left by n palces (appends
 * 0 from the right)
 *
 *  @param i Is the number of steps the contense  in the register is to be shifted to
 * the left
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *  
 *  Post-condition: Check if everything added through shifting is equal to zero
 *
 *  Properties:
 *  after shiftLeft(i, r), r equal to r << i
 */
void shiftLeft(int, iRegister *);

/** @brief Resets the i'th bit of the iRegister (to 0)
 *
 *  @param i Is i'th bit of the iRegister to be reset
 *
 *  @param r A pointer to a memory location of a iRegister data structure.
 *
 *  @return void
 *
 *  Pre-condition: 0 <= i < 32 and iRegister != Null
 *
 *  Post-condition: after reset(i, r) the i'th bit of iRegister is 0, all other
 *  bits remain unchanged
 *  properties:
 *  after resetBit(i, r),  getBit(i, r) = 0
 *  if getBit(i, r) == 0 then
 *    getBit(j, r) returns the same value for all
 *  0 <= j < 32 and j <> i before and after resetBit(i, r)
 */
void resetBit(int, iRegister *);

#endif
