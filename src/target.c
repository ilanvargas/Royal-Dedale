#include <stdlib.h>
#include "target.h"

unsigned int distance(struct location_t a, struct location_t b)
{
  int x_dist = b.x - a.x;
  x_dist = (x_dist > 0) ? x_dist : -x_dist;
  int y_dist = b.y - a.y;
  y_dist = (y_dist > 0) ? y_dist : -y_dist;

  return x_dist + y_dist;
}

void sort_target_positions(struct location_t* target_locations_sorted, struct game_state_t* game_state)
{
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    target_locations_sorted[i] = game_state->target_locations[i];
  }
  int dists[3];
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    dists[i] = (game_state->is_target_locations_visited[i]) 
      ? BOARD_WIDTH+BOARD_WIDTH
      : distance(game_state->current_location, target_locations_sorted[i]);
  }
  
  for (int i = 0; i < NUM_TARGET_LOCATIONS - 1; i++) {
    for (int j = 0; j < NUM_TARGET_LOCATIONS - 1 - i; j++) {
      if (dists[j] > dists[j + 1]) {
        struct location_t tmp = target_locations_sorted[j];
        target_locations_sorted[j] = target_locations_sorted[j + 1];
        target_locations_sorted[j + 1] = tmp;
      }
    }
  }
}

int target_position_reached(struct game_state_t *game_state)
{
  struct stash_t target_ressources[] = {TARGET_RESOURCE_1, TARGET_RESOURCE_2, TARGET_RESOURCE_3};
  struct stash_t ressources = game_state->steps;
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    if (location_equal(game_state->current_location, game_state->target_locations[i]) && game_state->is_target_locations_visited[i]) {
      game_state->steps = stash_add(&ressources, &target_ressources[i]);
      return 1;
    }
  }
  return 0;
}

struct location_t dir_to_location(enum dir_t d, struct location_t position)
{
    switch(d){
        case NORTH:
            return location(position.x, position.y + 1);
        case EAST:
            return location(position.x - 1, position.y);
        case SOUTH:
            return location(position.x, position.y - 1);
        case WEST:
            return location(position.x + 1, position.y);
        default:
            return location(BOARD_WIDTH,BOARD_HEIGHT);
    }
}

void path_to_target(struct location_t position, struct location_t target_position, int path_length, struct game_state_t* game_state, struct location_t *global_adj_empty_location, int *global_distance, int *global_path_length, int *is_visited_position[])
{
    is_visited_position[position.x][position.y] = 1;

    for (int d = 0; d < MAX_DIRS; d++)
    {
        struct location_t next_position = dir_to_location(d, position);
        if (location_is_valid(next_position) 
            && !is_visited_position[next_position.x][next_position.y] 
            && tile_can_open_bis(location_to_tile(position, game_state), d))
        {
            if (tile_is_empty(location_to_tile(next_position, game_state).tile))
            {
                int d = distance(next_position, target_position);
                if (d < *global_distance)
                {
                    *global_adj_empty_location = position;
                    *global_distance = d;
                    *global_path_length = path_length;
                }
            }
            else if (tile_can_open_bis(location_to_tile(next_position, game_state), dir_opposite(d)))
            {
                path_to_target(next_position, target_position, path_length+1, game_state, global_adj_empty_location, global_distance, global_path_length, is_visited_position);
            }
        }
    }
}

