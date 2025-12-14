#ifndef __DEDALE_TARGET_H__
#define __DEDALE_TARGET_H__

#include "game.h"

#define FINAL_RESOURCE \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES] = 1}  \
  }
#define BFINAL_RESOURCE \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES-1] = 1}  \
  }
#define BBFINAL_RESOURCE \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES-2] = 1}  \
  }

/** Calculates the Manhattan distance between two locations */
unsigned int distance(struct location_t a, struct location_t b);

/** Randomly selects 3 target positions and places them in the target_positions array 
 * the target_tiles array must be allocated before calling the function
*/
void select_target_positions(struct game_state_t* game_state, struct location_t* target_positions);

/** Sorts the target_positions array based on the Manhattan distance */
void sort_target_positions(struct location_t current_location, struct location_t* target_positions);

/** Initialise the game state and target positions and sort them based on starting location */
void init_game_state(unsigned int game_seed, struct location_t *target_positions, struct game_state_t *game_state);

/** converts a direction into a location based on the player's current location
 * no test if the returned location is valid
 */
struct location_t dir_to_location(enum dir_t d, struct location_t current_location);

/** chooses the next target position based on the number of visited target-positions */
struct location_t next_target_position(unsigned int num_visited_positions, struct location_t *target_positions);

/** checks if target position reached (exit tile included) 
 * if target position is reached the player gains the arrival resource of the target tile
 * returns 1 if target position is reached and 0 if not
*/
int target_position_reached(struct game_state_t *game_state, unsigned int num_visited_positions, struct location_t *target_positions);

/** recursive function to find the path of the return_empty_position which is the closest to next target position */
void find_path(struct game_state_t* game_state, struct location_t first_position, struct location_t target_postion, struct location_t *return_empty_location, int is_visited_position[BOARD_WIDTH][BOARD_HEIGHT], struct location_t path[BOARD_SIZE], int *path_length);



#endif  // __DEDALE_TARGET_H__
