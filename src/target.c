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

  if (!num_target_not_visited) return 0;
  
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
      printf("You have reached a target tile! You won a %s. Your ressources are now: %s\n", resource_to_string(NUM_RESOURCES-i), buffer);
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

void path_target_finder_rec(struct location_t position, 
    struct location_t target_position, 
    struct location_t* path_curr, 
    unsigned int path_len, 
    struct game_state_t* game_state, 
    int *global_dist, 
    struct location_t* global_path_curr, 
    unsigned int *global_path_len, 
    int is_visited_position[BOARD_WIDTH][BOARD_HEIGHT])
{
    is_visited_position[position.x][position.y] = 1;
    path_curr[path_len] = position;
    path_len++;

    // case where we didn't find a way to target
    if (path_len >= BOARD_SIZE) return;

    // case where rec position is the taget
    if (location_equal(position, target_position)) {
      *global_dist = 0;
      *global_path_len = path_len;
      for (unsigned int i = 0; i < path_len; i++) {
        global_path_curr[i] = path_curr[i];
      }
      is_visited_position[position.x][position.y] = 0;
      return;
    }

    // recursion
    for (int d = 0; d < MAX_DIRS; d++)
    {
        struct location_t next_position = dir_to_location(d, position);
        if (location_is_valid(next_position) 
            && !is_visited_position[next_position.x][next_position.y] 
            && tile_can_open_bis(location_to_tile(position, game_state), d))
        {
            if (tile_is_empty(location_to_tile(next_position, game_state).tile))
            {
                path_curr[path_len] = next_position;
                path_len++;
                int dist = distance(next_position, target_position);
                if (dist <= *global_dist && path_len < *global_path_len)
                {
                    *global_dist = dist;
                    *global_path_len = path_len;
                    for (unsigned int i = 0; i < path_len; i++) {
                       global_path_curr[i] = path_curr[i];
                    }
                }
                path_len--;
            }
            else if (tile_can_open_bis(location_to_tile(next_position, game_state), dir_opposite(d)))
            {
                path_target_finder_rec(next_position, 
                  target_position, 
                  path_curr, 
                  path_len, 
                  game_state, 
                  global_dist, 
                  global_path_curr, 
                  global_path_len, 
                  is_visited_position);
            }
        }
    }
    is_visited_position[position.x][position.y] = 0;
}

unsigned int path_target_finder(struct location_t target_location, struct game_state_t *game_state, struct location_t *path)
{
  struct location_t path_curr[BOARD_SIZE];
  unsigned int path_len = BOARD_SIZE;
  int dist = BOARD_SIZE;

  int is_visited_position[BOARD_WIDTH][BOARD_HEIGHT];
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      is_visited_position[i][j] = 0;
    }
  }

  path_target_finder_rec(game_state->current_location, 
    target_location, 
    path_curr, 
    0, 
    game_state, 
    &dist, 
    path, 
    &path_len, 
    is_visited_position);

  return path_len; 
}

void print_target_locations_sorted(struct location_t *target_locations_sorted, unsigned int num_target_locations)
{
  if (!num_target_locations) {
    printf("The exit tile is on the location (%d,%d)\n", BOARD_WIDTH-1, BOARD_HEIGHT-1);
    return;
  }

  printf("The target tiles are on the positons: ");
  for (unsigned int i = 0; i < num_target_locations; i++) {
    printf("(%d,%d) ", target_locations_sorted[i].x, target_locations_sorted[i].y);
  }
  printf("(sorted by proximity)\n");
}

void print_path_target(struct location_t *path, unsigned int path_len, struct location_t target)
{
  printf("\e[0;33mThe shortest path to target (%d,%d), or empty tile the nearest to target, found was:\n", target.x, target.y);
  for (unsigned int i = 0; i < path_len; i++) {
    printf("(%d,%d)", path[i].x, path[i].y);
  }
  printf("\e[0m\n");
}
