#include "cordic.h"
#include <stdio.h>
/* TODO:
 * see if I can generate better table values 
 * see if it is faster to use less temp variables and just directly use the variables */


/* a look up table for the 64 bit tangent angles for CORDIC */
const int64_t tanAngle64[64] = {
	0x1000000000000000, 0x0972028ECEF98400, 0x04FD9C2DAF71CF40, 0x028888EA0EEECD20, 0x014586A1872C4D80, 
	0x00A2EBF0AC823140, 0x00517B0F2E141318, 0x0028BE2A88EA2158, 0x00145F29A368619C, 0x000A2F975D98559C, 
	0x000517CC0048DD3D, 0x00028BE60A54065B, 0x000145F3066FF630, 0x0000A2F98360B979, 0x0000517CC1B57488, 
	0x000028BE60DB5D3D, 0x0000145F306DC2FE, 0x00000A2F9836E40A, 0x00000517CC1B7256, 0x0000028BE60DB935, 
	0x00000145F306DC9C, 0x000000A2F9836E4E, 0x000000517CC1B727, 0x00000028BE60DB93, 0x000000145F306DC9, 
	0x0000000A2F9836E4, 0x0000000517CC1B72, 0x000000028BE60DB9, 0x0000000145F306DC, 0x00000000A2F9836E, 
	0x00000000517CC1B7, 0x0000000028BE60DB, 0x00000000145F306D, 0x000000000A2F9836, 0x000000000517CC1B, 
	0x00000000028BE60D, 0x000000000145F306, 0x0000000000A2F983, 0x0000000000517CC1, 0x000000000028BE60, 
	0x0000000000145F30, 0x00000000000A2F98, 0x00000000000517CC, 0x0000000000028BE6, 0x00000000000145F3, 
	0x000000000000A2F9, 0x000000000000517C, 0x00000000000028BE, 0x000000000000145F, 0x0000000000000A2F, 
	0x0000000000000517, 0x000000000000028B, 0x0000000000000145, 0x00000000000000A2, 0x0000000000000051, 
	0x0000000000000028, 0x0000000000000014, 0x000000000000000A, 0x0000000000000005, 0x0000000000000002, 
	0x0000000000000001, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000
};

void cordic_sin_cos(int64_t angle, int64_t* sin, int64_t* cos){
	/* temp varaiables */
	int64_t tempCos;
	int64_t tempSin;
	int64_t sign = 0;
	/* temp variables for current values */
	int64_t curCos = 0x4DBA76D421AF3400;
	int64_t curSin = 0x0;
	/* iterate through the table and either add or subtract based on the
	 * atan(2^-i) angle from the table */
	for(int32_t i = 0; i < 64; i++){
		/* swap temp and current values */
		tempCos = curCos;
		tempSin = curSin;
		/* get the angle's current sign */
		sign = (angle >> 63);
		/* divide the angle by 2^i and either add or sub */
		curCos -= ((tempSin >> i) ^ sign) - sign;
		curSin += ((tempCos >> i) ^ sign) - sign;
		/* adjust current angle */
		angle -= (tanAngle64[i] ^ sign) - sign;
	}
	*sin = curSin;
	*cos = curCos;
}
