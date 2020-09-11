#ifndef _UNIVERSE_
#define _UNIVERSE_

/* TODO:
 *	implement move
 *	test structs */

/* This includes the structs and functions for everything associated with 
 * positions within the game. */

#include <stdint.h>

/* Position contains:
 *	x y and z intiger coordinates. */
struct Position {
	int64_t x;
	int64_t y;
	int64_t z;
};

/* Velocity contains:
 *	integer magnitude r.
 *	polar angle theta:
 *		rads = theta/(MAX_INT) * 2 pi.
 *	azimuthal angle phi:
 *		rads = phi/(MAX_INT) * 2 pi. */
struct Velocity {
	int32_t r;
	int64_t theta;
	int64_t phi;
};

/* INOMPLETE
 * This changes the position given a velocity.
 * Returns: 0 if the position change was sucessful. */
int move(struct Position* position, struct Velocity* velocity);
#endif
