/* This is for calculating the cordic table values.
 * I defently don't need to do it this way but it looked fun */

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
	COMPILER_INT values[COMPILER_INT_SIZE];
	double cosTheta = 1;
	double cosV;
	double temp;
	for(int i = 0; i<COMPILER_INT_SIZE; i++){
		temp = (atan(pow(2.0,-i)));
		if( temp > 2.0*M_PI ){
			printf("You messed something up\n"
					"temp = %f\n", temp);
		}
		cosV = cos(temp);
		cosTheta *= cosV;
		values[i] = (COMPILER_INT)((temp/(2.0*M_PI))*((double)COMPILER_INT_MAX));
		/*printf("cos = %f\n", cosV);
		printf("cosTheta = %f\n", cosTheta);
		printf("deg = %f\n", temp);*/
	}
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
	printf("\ncos = 0x%016llX\n",(COMPILER_INT)(COMPILER_INT_MAX*cosTheta));
	COMPILER_INT trueCos = cos((M_PI/2.0)*.25)*(double)COMPILER_INT_MAX;
	COMPILER_INT trueSin = sin((M_PI/2.0)*.25)*(double)COMPILER_INT_MAX;
	printf("true cos: %lld\n", trueCos);
	printf("true sin: %lld\n", trueSin);
}
