#include <stdio.h>
#include <inttypes.h>
#include "universe.h"
#include "cordic.h"

int32_t  move(struct Position* position, struct Velocity* velocity){
	/* Implement this algo using cordic:
	 * position.x += velocity.r*sin(velocity.theta)*cos(phi);
	 * position.y += velocity.r*sin(velocity.theta)*sin(phi);
	 * position.z += velocity.r*cos(velocity.theta); */

	/* temporary test for cordic function */
	double temp = 3.14159/2 * .25;
	int64_t angle = (int64_t)((temp/(2.0*3.14159))*(double)INT64_MAX);
	int64_t sin = 0;
	int64_t cos = 0;
	cordic_sin_cos(angle, &sin, &cos);
	printf("angle = %f\n", temp);
	printf("sin = %"PRId64" \ncos = %"PRId64"\n", sin, cos);
	return 0;
}
