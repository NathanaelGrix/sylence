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

/* Direction contains:
 *	8 bit intigers normalized for the direction that we are facing */ 
struct Direction {
	int8_t xFace;
	int8_t yFace;
	int8_t zFace;
};

/* Velocity contains: 
 *	a velocity with 64 bit components x, y, and z.*/
struct Velocity {
	int64_t x;
	int64_t y;
	int64_t z;
};

/*	32 bit integer velocity magintude r.
 *	polar angle theta:
 *		rads = theta/(0x4000000000000000) * 2pi.
 *	azimuthal angle phi:
 *		rads = phi/(0x4000000000000000) * 2pi. */

/* INCOMPLETE
 * This changes the position given a velocity.
 * Returns: 0 if the position change was sucessful. */
int32_t move(struct Position* position, struct Velocity* velocity);

/* INCOMPLETE
 * This removes some velocity dependent on the current velocity.
 * Returns: 0 if the velocity change was sucessful. */
int32_t drag(struct Velocity* velocity, int64_t dragFrom128);
#endif
