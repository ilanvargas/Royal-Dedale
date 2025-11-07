#include "location.h"
#include <stdlib.h>
#include <stdio.h>

/** Creates a location. */
struct location_t location(unsigned int x, unsigned int y)
{
    struct location_t l = {x,y};
    return l;
}

/** Checks if a location is valid with respect to the board dimensions. */
int location_is_valid(struct location_t loc)
{
    if (loc.x < BOARD_WIDTH)
    {
        if (loc.y < BOARD_HEIGHT)
            return 1;
    }
    return 0;
}

/** Checks if two locations are equal. */
int location_equal(struct location_t a, struct location_t b)
{
    if (location_is_valid(a) && location_is_valid(b))
    {
        if ( (a.x == b.x) && (a.y == b.y))
            return 1;
        else return 0;
    }
    else return 0;
}

/** Checks if two locations are adjacent. */
int location_is_adjacent(struct location_t a, struct location_t b)
{
    if (location_is_valid(a) && location_is_valid(b))
    {
        if ( a.x == b.x ) 
            if (a.y - b.y == 1 || b.y - a.y == 1) return 1;
            else return 0;
        else if ( a.y == b.y ) 
            if (a.x - b.x == 1 || b.x - a.x == 1) return 1;
            else return 0;
        else return 0;
    }
    else return 0;
}
