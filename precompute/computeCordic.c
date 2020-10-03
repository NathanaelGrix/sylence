/* This is for calculating the cordic table values.
 * I defently don't need to do it this way but it looked fun */

/* TODO:
 * get better table values
 * remove int size directives or add them to the rest of the game
 * improve cos start value accuracy */

#include <math.h>
#include <stdio.h>
#include <stdint.h>

#define COMPILER_INT_SIZE 64

#if COMPILER_INT_SIZE == 64
	#define COMPILER_INT_MAX INT64_MAX
	#define COMPILER_INT int64_t
#else
	#define COMPILER_INT_SIZE 32
	#define COMPILER_INT_MAX INT32_MAX
	#define COMPILER_INT int32_t
#endif



void main(){
	/* array of the tangent angles */
	COMPILER_INT values[COMPILER_INT_SIZE];
	
	/* cosin starting values */
	double cosTheta = 1;
	double cosV;
	double temp;

	/* generate the values */
	for(int i = 0; i<COMPILER_INT_SIZE; i++){

		/* get the tangent angle for the current power of 2 */
		temp = (atan(pow(2.0,-i)));
		if( temp > 2.0*M_PI ){
			printf("You messed something up\n"
					"temp = %f\n", temp);
		}
		/* get the cos value for the current angle */
		cosV = cos(temp);
		cosTheta *= cosV;
		/* convert the angle to a fixed point representation */
		values[i] = (double)0x2000000000000000 * (temp/M_PI);
	}
	/* print and format the table values so you can just copy and paste */
	printf("\n");
	for(int i = 0; i<COMPILER_INT_SIZE; i++){
#if COMPILER_INT_SIZE == 64
		printf("0x%016llX", values[i]);
#else
		printf("0x%08llX", values[i]);
#endif
		if(i<COMPILER_INT_SIZE - 1){
			printf(", ");
		}
		if(i%5 == 4){
			printf("\n");
		}
	}
	/* print the starting cos value */
	printf("\ncos = 0x%016llX\n",(COMPILER_INT)(0x4000000000000000*cosTheta));

	/* some true sin and cos refrence angles to compare to */
	COMPILER_INT trueCos = cos(M_PI/8.0)*(double)0x4000000000000000;
	COMPILER_INT trueSin = sin(M_PI/8.0)*(double)0x4000000000000000;
	printf("true cos(PI/4): %lld\n", trueCos);
	printf("true sin(Pi/4): %lld\n", trueSin);
	COMPILER_INT trueCos0 = cos(0.0)* (double)0x4000000000000000;
	COMPILER_INT trueSin0 = sin(0.0)* (double)0x4000000000000000;
	printf("true cos 0: %lld\n", trueCos0);
	printf("true sin 0: %lld\n", trueSin0);
}
