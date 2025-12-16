#include <stdlib.h>
#include <stdio.h>

#include "target.h"

unsigned int distance(struct location_t a, struct location_t b)
{
  int x_dist = b.x - a.x;
  x_dist = (x_dist > 0) ? x_dist : -x_dist;
  int y_dist = b.y - a.y;
  y_dist = (y_dist > 0) ? y_dist : -y_dist;

  return x_dist + y_dist;
}

int sort_target_locations(struct location_t* target_locations_sorted, struct game_state_t* game_state)
{
  int num_target_not_visited = 0;
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    target_locations_sorted[i] = game_state->target_locations[i];
  }
  int dists[NUM_TARGET_LOCATIONS];
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    if (game_state->is_target_locations_visited[i]) 
      dists[i] = BOARD_WIDTH+BOARD_WIDTH;
    else {
      dists[i] = distance(game_state->current_location, target_locations_sorted[i]);
      num_target_not_visited ++;
    }
  }
  
  for (int i = 0; i < NUM_TARGET_LOCATIONS - 1; i++) {
    for (int j = 0; j < NUM_TARGET_LOCATIONS - 1 - i; j++) {
      if (dists[j] > dists[j + 1]) {
        struct location_t tmp = target_locations_sorted[j];
        target_locations_sorted[j] = target_locations_sorted[j + 1];
        target_locations_sorted[j + 1] = tmp;

        int tmp_d = dists[j];
        dists[j] = dists[j + 1];
        dists[j + 1] = tmp_d;
      }
    }
  }
  return num_target_not_visited;
}

int target_location_reached(struct game_state_t *game_state)
{
  struct stash_t target_ressources[] = {TARGET_RESOURCE_1, TARGET_RESOURCE_2, TARGET_RESOURCE_3};
  struct stash_t ressources = game_state->steps;
  for (int i = 0; i < NUM_TARGET_LOCATIONS; i++) {
    if (location_equal(game_state->current_location, game_state->target_locations[i]) && !game_state->is_target_locations_visited[i]) {
      game_state->steps = stash_add(&ressources, &target_ressources[i]);

      char buffer[MAX_STASH_STRING_LENGTH];
      struct stash_t r = game_state->steps;
      stash_to_string(&r, buffer);
      printf("You have reached a target tile! Your ressources are now: %s\n", buffer);
      game_state->is_target_locations_visited[i] = 1;
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

void path_to_target(struct location_t position, struct location_t target_position, struct location_t* path_curr, int path_length, struct game_state_t* game_state, struct location_t *global_adj_empty_location, int *global_distance, struct location_t* global_path_curr, int *global_path_length, int *is_visited_position[])
{
    is_visited_position[position.x][position.y] = 1;
    path_length ++;
    path_curr[path_length] = position;

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
                    for (int i = 0; i < path_length; i++) {
                       global_path_curr[i] = path_curr[i];
                    }
                }
            }
            else if (tile_can_open_bis(location_to_tile(next_position, game_state), dir_opposite(d)))
            {
                  path_to_target(
                      next_position,
                      target_position,
                      path_curr,
                      path_length,
                      game_state,
                      global_adj_empty_location,
                      global_distance,
                      global_path_curr,
                      global_path_length,
                      is_visited_position
                  );
            }
        }
    }
}

void print_target_locations_sorted(struct location_t *target_locations_sorted, unsigned int num_target_locations)
{
  printf("The target tiles are on the positons: ");
  for (unsigned int i = 0; i < num_target_locations; i++) {
    printf("(%d,%d) ", target_locations_sorted[i].x, target_locations_sorted[i].y);
  }
  printf("(sorted by proximity)\n");
}

