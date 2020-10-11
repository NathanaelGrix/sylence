#include <stdio.h>
#include <inttypes.h>
#include "universe.h"
#include "cordic.h"

/* TODO:
 * add support for angles greater then PI/2 and less then zero 
 * add meaning to the return or remove entirely 
 * remove print statements when it is fully opperational 
 * Optimize
 * remove math library
 * */

int32_t  move(struct Position* position, struct Velocity* velocity){
	/* Implement this algo using cordic:
	 * position.x += velocity.r*sin(velocity.theta)*cos(phi);
	 * position.y += velocity.r*sin(velocity.theta)*sin(phi);
	 * position.z += velocity.r*cos(velocity.theta); */

	/* angle conversions */
	int64_t sinTheta;
	int64_t cosTheta;
	int64_t sinPhi;
	int64_t cosPhi;

	/* temporary test for cordic function */

	printf("\nr: 0x%016"PRIX64"\ntheta: 0x%016"PRIX64"\nphi: 0x%016"PRIX64"\n\n", velocity->r, velocity->theta, velocity->phi);
	
	/* Get the angles converted to cos and sin */
	cordic_sin_cos(velocity->theta, &sinTheta, &cosTheta);
	printf("CORDIC sin(theta) : %f\n", (double)sinTheta/(double)0x4000000000000000);
	printf("CORDIC cos(theta) : %f\n", (double)cosTheta/(double)0x4000000000000000);
	cordic_sin_cos(velocity->phi,   &sinPhi,   &cosPhi  ); 
	printf("CORDIC sin(phi  ) : %f\n", (double)sinPhi  /(double)0x4000000000000000);
	printf("CORDIC cos(phi  ) : %f\n", (double)cosPhi  /(double)0x4000000000000000);
	
	/* Pint out to make sure that they are valid */
	printf("sinTheta: 0x%016"PRIX64"\tcosTheta: 0x%016"PRIX64"\n", sinTheta, cosTheta);
	printf("sinPhi  : 0x%016"PRIX64"\tcosPhi  : 0x%016"PRIX64"\n", sinPhi  , cosPhi  );

	printf("position.x before: 0x%016"PRIX64"\n", position->x);
	position->x += cordic_hi_mul( cordic_hi_mul(velocity->r,sinTheta) << 2 , cosPhi) << 2;
	printf("position.x after:  0x%016"PRIX64"\n", position->x);

	printf("position.y before: 0x%016"PRIX64"\n", position->y);
	position->y += cordic_hi_mul( cordic_hi_mul(velocity->r,sinTheta) << 2 , sinPhi) << 2;
	printf("position.y after:  0x%016"PRIX64"\n", position->y);
	
	printf("position.z before: 0x%016"PRIX64"\n", position->z);
	position->z += cordic_hi_mul( velocity->r, cosTheta) << 2;
	printf("position.z after:  0x%016"PRIX64"\n", position->z);
	return 0;
}
