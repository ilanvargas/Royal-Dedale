#ifndef __DEDALE_TARGET_H__
#define __DEDALE_TARGET_H__

#include "game.h"

#define TARGET_RESOURCE_1 \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES-2] = 1}  \
  }
#define TARGET_RESOURCE_2 \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES-1] = 1}  \
  }
#define TARGET_RESOURCE_3 \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES] = 1}  \
  }

/** Calculates the Manhattan distance between two locations 
 */
unsigned int distance(struct location_t a, struct location_t b);

/** Sorts the target_positions array based on the Manhattan distance. 
 * Simple bubble sort for a short array
 *
 * Returns number of not visited target tiles
 * 
 * Visited locations stays at the end of the array
 *
 * The target_locations_sorted array must be allocated before calling this function and be able to 
 * contain at least NUM_TARGET_LOCATIONS location_t
 */
int sort_target_locations(struct location_t* target_locations_sorted, struct game_state_t* game_state);

/** Checks if target position reached 
 * 
 * If target position is reached the player gains the target associeted resource
 * 
 * Returns 1 if target position is reached and 0 if not
*/
int target_location_reached(struct game_state_t *game_state);

/** Find the empty tile that can be open the closest to the closest target tile
 */
void path_to_target(struct location_t position, struct location_t target_position, struct location_t* path_curr, int path_length, struct game_state_t* game_state, struct location_t *global_adj_empty_location, int *global_distance, struct location_t* global_path_curr, int *global_path_length, int *is_visited_position[]);

/** Print interface sorted target positions
 */
void print_target_locations_sorted(struct location_t *target_locations_sorted, unsigned int num_target_locations);

#endif  // __DEDALE_TARGET_H__
