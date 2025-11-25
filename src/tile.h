#ifndef __DEDALE_TILE_H__
#define __DEDALE_TILE_H__

#include "dir.h"
#include "stash.h"

/** The number of tiles that are generated each turn, the player must
 * select one among them */
#ifndef NUM_TILES_PER_TURN
#define NUM_TILES_PER_TURN 3
#endif  // NUM_TILES_PER_TURN

/** Abstract struct representing a tile. A tile is identified by its name,
    its traversal cost, and its opening costs in each direction.
 */
struct tile_t;

#ifndef MAX_TILE_NAME_LENGTH
#define MAX_TILE_NAME_LENGTH 40
#endif // MAX_TILE_NAME_LENGTH

extern struct tile_t EMPTY_TILE;
extern struct tile_t START_TILE;
extern struct tile_t EXIT_TILE;
extern struct tile_t CLOISTER_TILE;
extern struct tile_t N_TERRACE_TILE;
extern struct tile_t E_TERRACE_TILE;
extern struct tile_t W_TERRACE_TILE;
extern struct tile_t S_TERRACE_TILE;
extern struct tile_t EW_CORRIDOR_TILE;
extern struct tile_t NS_CORRIDOR_TILE;
extern struct tile_t* p_tiles[];

#ifndef TILES_NUMBER
#define TILES_NUMBER 10
#endif // TILES_NUMBER

/** Initializes the tiles depending on an integer `tile_seed`. Can be
    called multiple times. Can prepare the tiles depending on the integer
    `tile_seed`. Can also do nothing.
 */
void init_tiles(unsigned int tile_seed);

/** Returns the name of the tile. */
const char* tile_name(const struct tile_t* tile);

/** Returns the traversal cost of the tile. This cost must be paid each
 * time the player traverses the tile. */
struct stash_t tile_traversal_cost(const struct tile_t* tile);

/** Returns the opening cost of the tile in a specific direction. This cost
 * must be paid only the first time the player places the tile in the game. */
struct stash_t tile_opening_cost(const struct tile_t* tile, enum dir_t d);

/** Creates an empty tile. These tiles are placeholders for the real tiles
 * in the game. They are not supposed to be placed or traversed. */
struct tile_t* tile_generate_empty();

/** Creates a start tile. A start tile can open in any direction. */
struct tile_t* tile_generate_start();

/** Creates an exit tile. An exit tile can open in any direction. */
struct tile_t* tile_generate_exit();

/** Creates a tile with the name `name`. Returns NULL if not existing. */
struct tile_t* tile_generate_by_name(const char* name);

/** Randomly generates multiple tiles opening to a specific direction. For
 * example, if `d` is SOUTH, it will generate tiles that can be opened to
 * the SOUTH.
 *
 * The number of generated tiles is at most `NUM_TILES_PER_TURN`. The
 * actual number of generated tiles is returned, and the generated tiles
 * are stored in the `results` array.
 *
 * The `results` array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 */
unsigned int tile_draft(enum dir_t d, struct tile_t** results);

/** Returns 1 if the tile is empty, 0 otherwise. */
int tile_is_empty(const struct tile_t* tile);

/** Returns 1 if the tile can be opened in the specified direction, 0
 * otherwise. A tile can be opened in direction `d` if it has a finite
 * opening cost in the direction `d`. */
int tile_can_open(const struct tile_t* tile, enum dir_t d);

#endif  // __DEDALE_TILE_H__
