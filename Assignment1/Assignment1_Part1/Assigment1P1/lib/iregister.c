#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"

void resetBit(int i, iRegister *r)
{
	// pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
		return;
	}
	// pre-condition
	if( i < 0 || i > 31)
	{
		fprintf(stderr,"Error: Invalid bit\n");
		return;
	}
	
  	r->content &= ~(1 << i);

	// post-condition
	if((r->content & (1<<i)) != 0)
	{
		fprintf(stderr, "Error: Failed to reset Bit\n");
		return;	
	}
}


/** resets all the bits of the iRegister (to 0)
 */ 
void resetAll(iRegister *r){
    // pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetAll\n");
		return;
	}
	
    r->content = 0;
    
    // post-condition
	if(r->content != 0)
	{
		fprintf(stderr, "Error: Failed to reset Bits\n");
		return;	
	}
}


/** sets the i'th bit of the iRegister (to 1)
 */
void setBit(int i, iRegister *r){
// pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to setBit\n");
		return;
	}
	// pre-condition
	if( i < 0 || i > 31)
	{
		fprintf(stderr,"Error: Invalid bit\n");
		return;
	}
	
  	r->content |= (1 << i);

	// post-condition
	if((r->content & 1<<i) == 0)
	{
		fprintf(stderr, "Error: Failed to set Bit\n");
		return;	
	}
}

/**sets all the bits of the iRegister (to 1)
 */
void setAll(iRegister *r){
    // pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to setAll\n");
		return;
	}
	
    r->content = 0xFFFFFFFF;
    
    // post-condition
	if(r->content != 0xFFFFFFFF)
  {
		fprintf(stderr, "Error: Failed to set Bits\n");
		return;	
	}
}


/** returns the i'th bit of the iRegister as an integer (1 if it is set, or 0 otherwise)
 */
int getBit(int i, iRegister *r){
    // pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to getBit\n");
		return -1;
	}
	
	// pre-condition
	if( i < 0 || i > 31)
	{
		fprintf(stderr,"Error: Invalid bit\n");
		return -1;
	}
	
	//if bit i set return 1 else else return 0
	if(r->content & 1 << i){
	    return 1;
	}else
	
	return 0;
    
}


/** set the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 */
void assignNibble(int i, int y, iRegister *r){
    // pre-condition
    if(r == NULL)
    {
        fprintf(stderr, "Error: A NULL pointer was given to getBit\n");
        return;
    }

    // pre-condition
    if( y <= 0 || y > 15)
    {
        fprintf(stderr,"Error: Invalid size!\n");
        return;
    }

    // pre-condition
    if( i < 0 || i > 7)
    {
        fprintf(stderr,"Error: Invalid nibble pos!\n");
        return;
    }

    r->content ^= y<<(i*4);

    //post-condition, Check if selected nibble now equals to slected value
    if((((0xF<<i*4) & r->content) >> i*4)!=y){
        fprintf(stderr,"Nibble was not assigned!\n");
        return;
    }


}


/** get the first (for pos=1) or the second (for pos=2) four bits of iRegsiter
 */
int getNibble(int i, iRegister *r){
    
    if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to getNibble\n");
		return -1;
	}
	// pre-condition
	if( i < 0 || i > 7)
	{
		fprintf(stderr,"Error: Invalid nibble pos!\n");
		return -1;
	}
	
	//1111 shift to same numbered nibble u want then bitwise and with content of r
	return ((0xF<<i*4) & r->content) >> i*4;
	
	
    
}


/** returns a pointer to an array of 32 characters, with each character 
 *  representing the corresponding bit of the iRegister, i.e., if the bit is set,
 *  then the character is "1" (ASCII char with code 49), or otherwise is "0" 
 *  (ASCII char with code 48)
 */
char *reg2str(iRegister r){
	//create and allocate array
	char *reg_string = malloc(33);
  
  //check if malloc was successful
  if(reg_string==NULL){
    fprintf(stderr, "Error: A NULL pointer was given\n");
		return NULL;
  }

	//Create endpoint of string
	reg_string[32]='\0';
    
	/*Setting the bits from MSB(Most significant Bit) to LSB(Least significant bit),
	 the register and the array have the opposite indexing.*/
	for(int i=31; i >=0; i--){
		if(r.content & (1 << i)){
			reg_string[31-i] = '1';
		}else
			reg_string[31-i] = '0';
	}
    
	//return the finalized "copy"
	return reg_string;
}


/** shifts all the bits of the iRegister to the right by n palces (appends 0 
 *  from the left)
 */
void shiftRight(int i, iRegister *r){
    // pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to shiftRight\n");
		return;
	}
	
	// pre-condition
	if( i < 0 || i > 31)
	{
		fprintf(stderr,"Error: Invalid bit\n");
		return;
	}

  //shift i steps to the right 
	r->content = r->content >> i;

  //Make sure that everything is left as 0 when shifted
  for(int y=0; y<i; y++){
    resetBit(31-y,r);
  }
    
}


/** shifts all the bits of the iRegister to the left by n palces (appends 0 
 *  from the right)
 */
void shiftLeft(int i, iRegister *r){
    // pre-condition
	if(r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to shiftLeft\n");
		return;
	}
	
	// pre-condition
	if( i < 0 || i > 31)
	{
		fprintf(stderr,"Error: Invalid bit\n");
		return;
	}
	
	r->content = r->content<<i;
	
	//Post-condition
	for(int y=0; y<i; y++){
    if(getBit(y,r)){
      fprintf(stderr, "Error with shifting");
      return;
    }
         
  }
    
}


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
 * 
 *  test-cases: 
 *  1,2,3. Allocate memory to an iRegister r
 *  first do resetAll(&r),
 *  then set the i'th bit of &x by setBit(i, &r) for i = 0, 15 and 23 and then
 *  display the result after each and every call by 
 *    printf("%s",reg2str(r)) 
 */
