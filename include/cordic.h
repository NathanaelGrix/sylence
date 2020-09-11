#ifndef _CORDIC_
#define _CORDIC_

/* This is for the cordic implementation for an int sin and cos function */

#include <stdint.h>

/* Calculates the sin and cos given an angle
 * input: 
 *	angle as a fixed point var(where 0 = 0 and 2PI = MAX_INT) between 0 and PI/2
 * output:
 *	sin of the angle where 0 = 0 and 1 = MAX_INT
 *	cos of the angle where 0 = 0 and 1 = MAX_INT */
void cordic_sin_cos(int64_t angle, int64_t* sin, int64_t* cos);
#endif
