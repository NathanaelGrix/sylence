#ifndef _CORDIC_
#define _CORDIC_

/* This is for coordinate related functions */

#include <stdint.h>

/* Calculates the sin and cos given an angle
 * input: 
 *	angle as a fixed point var(where 0 = 0 and 2PI = 0x4000000000000000) between -PI/2 and PI/2
 * output:
 *	sin of the angle where 0 = 0 and 1 = 0x4000000000000000
 *	cos of the angle where 0 = 0 and 1 = 0x4000000000000000 */
void cord_sin_cos(int64_t angle, int64_t* sin, int64_t* cos);

/* calculates the upper half of two large 64 bit numbers being multiplied 
 * input:
 *	the first number being multiplied
 *	the second number being multiplied
 *output:
	the upper 64 bits of a 128 bit multiply*/
int64_t cord_hi_mul(int64_t num1, int64_t num2);
#endif
