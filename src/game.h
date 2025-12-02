#ifndef __DEDALE_GAME_H__
#define __DEDALE_GAME_H__

#include "tile.h"
#include "location.h"

/** The current state of the mansion & player
 */
struct game_state_t {
  struct stash_t steps;
  struct tile_t* board[BOARD_WIDTH][BOARD_HEIGHT];
  struct location_t current_location;
};

void init_state(unsigned int game_seed, struct game_state_t* game_state);

/** Verifies if the player reached the exit
 */
int exit_reached(struct game_state_t* game_state);

/** Lists every location of empty tile that can be open adjecent to the location of the player
 * 
 * The number of locations of adjacent tiles is at most equal to 4
 *
 * The array 'possible_locations' must be allocated before calling the fuction
 *
 * Return the length of 'possible_locations'
 */
unsigned int list_empty_locations_with_finite_opening_cost(struct location_t* possible_locations, struct game_state_t* game_state);

/** Asks the payer if he wants to place a tile
 *
 * Returns bool value
 */
int decide_to_place_tile(int is_iterative);

/** Randomly generates multiple tiles with tile_draft in tile.c 
 *
 * The 'available_tiles' array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 *
 * Returns the length of 'available_tiles'
 */
unsigned int generate_some_tiles(struct location_t l, struct tile_t** available_tiles, struct game_state_t* game_state);

/** Asks the player to select a location of the array 'possible_locations' of size 'length'
 * 
 * Returns the selected location
 */
struct location_t select_location(int is_iterative, struct location_t* possible_locations, int length);

/** Asks the player to select a tile of the array 'tiles' of size 'length'
 * 
 * Returns the selected tile's pointer
 */
struct tile_t* select_tile(int is_iterative, struct tile_t** available_tiles, int length);

/** Place a tile 'tile' in 'location' in the board of game_state
 */
void place_tile(struct location_t l, struct tile_t* tile, struct game_state_t* game_state);

/** Lists every open tile adjecent to the location of the player
 * 
 * The number of locations of adjacent tiles is at most equal to 4
 *
 * The array 'possible_locations' must be allocated before calling the functions 
 *
 * Return the length of 'possible_locations'
 */
int list_open_location(struct location_t* possible_locations, struct game_state_t* game_state);

/** Move the location of the player in game_state to 'location'
 */
void move_player(struct location_t l, struct game_state_t* game_state);

#endif //__DEDALE_GAME_H__
