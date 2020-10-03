#ifndef _UNIVERSE_
#define _UNIVERSE_

/* This includes the structs and functions for everything associated with 
 * location and movement within the game. */

#include <stdint.h>

/* Position contains:
 *	64 bit intiger coordinates x, y, and z. */
struct Position {
	int64_t x;
	int64_t y;
	int64_t z;
};

/* Velocity contains:
 *	32 bit integer velocity magintude r.
 *	polar angle theta:
 *		rads = theta/(0x4000000000000000) * 2pi.
 *	azimuthal angle phi:
 *		rads = phi/(0x4000000000000000) * 2pi. */
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
