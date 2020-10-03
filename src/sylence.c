/* this is the game's starting point */

/* currently doesnt do anyting other than test cordic */

#include <stdio.h>
#include <stdint.h>
#include "universe.h"

int main() {
	struct Position position = { 0x10000000,0x10000000,0x10000000 };
	struct Velocity velocity = { 0xFFFF, 
		(int64_t)( (double)0x4000000000000000 * (3.14159/4) / (2*3.14159) ) ,
		(int64_t)( (double)0x4000000000000000 * (3.14159/4) / (2*3.14159) )};
	move( &position, &velocity );
	return 0;
}
