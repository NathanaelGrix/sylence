/* this is the game */

/* currently doesnt do anyting other than test cordic */

#include <stdio.h>
#include <stdint.h>
#include "universe.h"

int main() {
	struct Position position = { 0,0,0 };
	struct Velocity velocity = { 0,0,0 };
	move( &position, &velocity );
	return 0;
}
