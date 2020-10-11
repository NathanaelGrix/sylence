#include "cordic.h"
#include <stdio.h>
/* TODO:
 * see if I can generate better table values 
 * see if it is faster to use less temp variables and just directly use the variables 
 * create a function to multiply by cos and sin output
 * Optimize the multiply function for use with cordic
 * See if you can make the multiply chop off less bits
 * carry bit is already discarded so remove carry math
 * fix this mess that you were using to make all 4 quadrents work
 * */


/* a look up table for the 64 bit tangent angles for CORDIC */
const int64_t tanAngle64[64] = {
0x0800000000000000, 0x04B90147677CC200, 0x027ECE16D7B8E7A0, 0x0144447507776690, 0x00A2C350C39626C0, 
0x005175F8564118A0, 0x0028BD87970A098C, 0x00145F15447510AC, 0x000A2F94D1B430CE, 0x000517CBAECC2ACE, 
0x00028BE600246E9E, 0x000145F3052A032D, 0x0000A2F98337FB18, 0x0000517CC1B05CBC, 0x000028BE60DABA44, 
0x0000145F306DAE9E, 0x00000A2F9836E17F, 0x00000517CC1B7205, 0x0000028BE60DB92B, 0x00000145F306DC9A, 
0x000000A2F9836E4E, 0x000000517CC1B727, 0x00000028BE60DB93, 0x000000145F306DC9, 0x0000000A2F9836E4, 
0x0000000517CC1B72, 0x000000028BE60DB9, 0x0000000145F306DC, 0x00000000A2F9836E, 0x00000000517CC1B7, 
0x0000000028BE60DB, 0x00000000145F306D, 0x000000000A2F9836, 0x000000000517CC1B, 0x00000000028BE60D, 
0x000000000145F306, 0x0000000000A2F983, 0x0000000000517CC1, 0x000000000028BE60, 0x0000000000145F30, 
0x00000000000A2F98, 0x00000000000517CC, 0x0000000000028BE6, 0x00000000000145F3, 0x000000000000A2F9, 
0x000000000000517C, 0x00000000000028BE, 0x000000000000145F, 0x0000000000000A2F, 0x0000000000000517, 
0x000000000000028B, 0x0000000000000145, 0x00000000000000A2, 0x0000000000000051, 0x0000000000000028, 
0x0000000000000014, 0x000000000000000A, 0x0000000000000005, 0x0000000000000002, 0x0000000000000001, 
0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 };

const int64_t xSigns[4] = {
0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000
};

const int64_t ySigns[4] = {
0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF
};

const int64_t xyFlip[4] = {
0x0000000000000000, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF
};


int64_t cordic_hi_mul(int64_t num1, int64_t num2){
	/* grab the sign of the two numbers */
	int64_t sign = (num1 >> 63) ^ (num2 >> 63);
	/* convert to absolute value */
	uint64_t temp = num1 >> 63;
	num1 ^= temp;
	num1 += temp & 1;
	temp = num2 >> 63;
	num2 ^= temp;
	num2 += temp & 1;
	/* seperate the multiplication into smaller chunks */
	uint64_t    lo1 = (uint32_t)num1;
	uint64_t    hi1 = num1 >> 32;
	uint64_t    lo2 = (uint32_t)num2;
	uint64_t    hi2 = num2 >> 32;
	/* multiply the chunks */
	uint64_t    hihi =  hi1 * hi2;
	uint64_t    hilo = hi1 * lo2;
	uint64_t    lohi = lo1 * hi2;

	/* uint64_t    lolo =  lo1 * lo2; */
	/* calculate the cary bit */
	/* uint64_t    carry_bit = ((uint64_t)(uint32_t)hilo + (uint64_t)(uint32_t)lohi + (lolo >> 32) ) >> 32; */

	/* get the high value of the multiplication */
	uint64_t    multhi = hihi + (hilo >> 32) + (lohi >> 32) /*+ carry_bit*/;
	/* return the high with the correct sign */
	return ((int64_t)multhi ^ sign) - sign;
}	

void cordic_sin_cos(int64_t angle, int64_t* sin, int64_t* cos){
	/* Get it to be an angle between 0x0 and 0x0FFFFFFFFFFFFFFF */
	int64_t quad = (angle & 0x3000000000000000) >> 60;
	angle = angle & 0x0FFFFFFFFFFFFFFF;
	/* temp varaiables */
	int64_t sign;
	int64_t tempCos;
	int64_t tempSin;
	/* temp variables for current values */
	int64_t curCos = 0x26DD3B6A10D79A00;
	int64_t curSin = 0x0;
	/* iterate through the table and either add or subtract based on the
	 * atan(2^-i) angle from the table */
	for(int32_t i = 0; i < 64-3; i++){
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
	/* flip the sin and cos if needed for the quadrent */
	tempSin = (curSin & ~xyFlip[quad]) | (curCos & xyFlip[quad]);
	tempCos = (curCos & ~xyFlip[quad]) | (curSin & xyFlip[quad]);
	/* return the sin and cos but give the appropriate signs for the quadrent */
	*sin = (tempSin ^ ySigns[quad]) - ySigns[quad];
	*cos = (tempCos ^ xSigns[quad]) - xSigns[quad];
}

