/* this is the game's starting point */

/* currently doesnt do anyting other than test cordic */

#include <stdio.h>
#include <stdint.h>
/* remove */
#include <math.h>
#include "universe.h"

int main() {
	double theta = -17*M_PI/8;
	double phi = 0.0;
	struct Position position = { 0x10000000,0x10000000,0x10000000 };
	struct Velocity velocity = { 0xFFFF, 
		(int64_t)( (double)0x4000000000000000 * (theta) / (2*M_PI) ),
		(int64_t)( (double)0x4000000000000000 * (phi  ) / (2*M_PI) )};

	printf("sin(theta) : %f\n", sin(theta));
	printf("cos(theta) : %f\n", cos(theta));
	printf("sin( phi ) : %f\n", sin(phi  ));
	printf("cos( phi ) : %f\n", cos(phi  ));
	move( &position, &velocity );
	return 0;
}
