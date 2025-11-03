#ifndef __DEDALE_LOCATION_H__
#define __DEDALE_LOCATION_H__

/** The width of the board, in number of tiles. */
#ifndef BOARD_WIDTH
#define BOARD_WIDTH 5
#endif

/** The height of the board, in number of tiles. */
#ifndef BOARD_HEIGHT
#define BOARD_HEIGHT 5
#endif

/** The total number of tiles in the board. */
#define BOARD_SIZE (BOARD_WIDTH * BOARD_HEIGHT)

/** Structure representing a location on the board.
 *
 * The valid locations on the board range from (0,0) (bottom-left corner) to
 * (BOARD_WIDTH-1, BOARD_HEIGHT-1) (top-right corner).
 */
struct location_t {
  unsigned int x;
  unsigned int y;
};

/** Creates a location. */
struct location_t location(unsigned int x, unsigned int y);

/** Checks if a location is valid with respect to the board dimensions. */
int location_is_valid(struct location_t loc);

/** Checks if two locations are equal. */
int location_equal(struct location_t a, struct location_t b);

/** Checks if two locations are adjacent. */
int location_is_adjacent(struct location_t a, struct location_t b);

#endif  // __DEDALE_LOCATION_H__
