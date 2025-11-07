#include "location.h"

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
    if (location_is_valid(a) == 1)
    {
        if (location_is_valid(b) == 1)
        {
            if (a.x == b.x)
            {
                if (a.y == b.y)
                    return 1;
            }
        }
    }
    return 0;
}

/** Checks if two locations are adjacent. */
int location_is_adjacent(struct location_t a, struct location_t b);
