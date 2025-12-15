#ifndef __DEDALE_GAME_H__
#define __DEDALE_GAME_H__

#include "tile_bis.h"
#include "location.h"

#define NUM_INITIAL_ROTATIONS BOARD_WIDTH * BOARD_HEIGHT / 10 

#define NUM_TARGET_LOCATIONS 3

/** The current state of the mansion & player
 */
struct game_state_t {
  struct stash_t steps;
  struct tile_bis_t board[BOARD_WIDTH][BOARD_HEIGHT];
  struct location_t current_location;

  struct location_t target_locations[NUM_TARGET_LOCATIONS];
  int is_target_locations_visited[NUM_TARGET_LOCATIONS];
};

void init_state(unsigned int game_seed, struct game_state_t* game_state);

/** Returns adress of tile in location in the board
 */
struct tile_bis_t location_to_tile(struct location_t l, struct game_state_t* game_state);

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

/** With a location adjacent to the player gives it direction to the player's location
 */
enum dir_t location_to_dir(struct location_t l, struct game_state_t* game_state);

/** Asks the player to select a location of the array 'possible_locations' of size 'length'
 * 
 * Returns the selected location
 */
struct location_t select_location(int is_iterative, struct location_t* possible_locations, int length);

/** Asks the player to select a tile of the array 'tiles' of size 'length'
 * 
 * Returns the selected tile's pointer
 */
struct tile_bis_t select_tile(int is_iterative, struct tile_bis_t* available_tiles, int length);

/** Place a tile 'tile' in 'location' in the board of game_state
 */
void place_tile(struct location_t l, enum dir_t d, struct tile_bis_t tile, struct game_state_t* game_state);

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

/** Rotate the tile randomly if the player want it
 *
 * Consumes num_rotations
 */
void random_tile_rotation(int is_interactive, struct tile_bis_t tile, enum dir_t d, int* num_rotations);

#endif //__DEDALE_GAME_H__
