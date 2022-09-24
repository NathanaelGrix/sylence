#include <stdio.h>
#include <inttypes.h>
#include "universe.h"
#include "cord.h"

/* TODO:
 * add meaning to the return or remove entirely
 * fix the drag so you can use more values
 * make the sign fixing more compact */
int32_t move(struct Position* position, struct Velocity* velocity){
	(*position).x += (*velocity).x;
	(*position).y += (*velocity).y;
	(*position).z += (*velocity).z;

	return 0;
}

int32_t drag(struct Velocity* velocity, int64_t dragFrom128){
	int64_t sign;
	sign = (*velocity).x>>63;
	(*velocity).x ^= sign;
	(*velocity).x -= sign;

	(*velocity).x *= dragFrom128;
	(*velocity).x >>= 7;

	(*velocity).x ^= sign;
	(*velocity).x -= sign;

	sign = (*velocity).y>>63;
	(*velocity).y ^= sign;
	(*velocity).y -= sign;

	(*velocity).y *= dragFrom128;
	(*velocity).y >>= 7;

	(*velocity).y ^= sign;
	(*velocity).y -= sign;

	sign = (*velocity).z>>63;
	(*velocity).z ^= sign;
	(*velocity).z -= sign;

	(*velocity).z *= dragFrom128;
	(*velocity).z >>= 7;

	(*velocity).z ^= sign;
	(*velocity).z -= sign;
}
