#include "game.h"
#include <stdio.h>
#include <stdlib.h>

/** Returns adress of tile in location in the board
 */
struct tile_t* location_to_tile(struct location_t l, struct game_state_t* game_state)
{
  return game_state->board[l.x][l.y];
}

void init_state(unsigned int game_seed, struct game_state_t* game_state)
{
  game_state->steps.r[STEP] = 4 * BOARD_SIZE / 3;
  
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      game_state->board[i][j] = tile_generate_empty();
    }
  }
  game_state->board[0][0] = tile_generate_start();
  game_state->board[BOARD_WIDTH-1][BOARD_HEIGHT-1] = tile_generate_exit();

  game_state->current_location = location(0, 0);

  srand(game_seed);
}

int exit_reached(struct game_state_t* game_state)
{
  return tile_generate_exit() == location_to_tile(game_state->current_location, game_state);
}

unsigned int list_empty_locations_with_finite_opening_cost(struct location_t* possible_locations, struct game_state_t* game_state)
{
  struct location_t current_location = game_state->current_location;
  int i = 0;    

  struct location_t adj_tiles[MAX_DIRS] = {
    [NORTH] = location(current_location.x, current_location.y+1),
    [SOUTH] = location(current_location.x, current_location.y-1),
    [EAST] = location(current_location.x+1, current_location.y),
    [WEST] = location(current_location.x-1, current_location.y)
  };
  for (int d = 0; d < MAX_DIRS; d++) {
    if (tile_can_open(location_to_tile(current_location, game_state), d)) {
      if (location_is_valid(adj_tiles[d]) && tile_is_empty(location_to_tile(adj_tiles[d], game_state))) {
        possible_locations[i] = adj_tiles[d];
        i ++;
      }
    }
  }
  return i;
}

int decide_to_place_tile()
{
  printf("Do you want to place or move?\n");
  int choice = rand()%2;
  if (choice) {
    printf(">> Place\n");
    return 1;
  }
  printf(">> Move\n");
  return 0;
}

unsigned int generate_some_tiles(struct location_t l, struct tile_t** available_tiles, struct game_state_t* game_state)
{
  struct location_t current_location = game_state->current_location;
  if (!location_is_adjacent(l, current_location)) return -1;

  struct location_t adj_tiles[MAX_DIRS] = {
    [NORTH] = location(current_location.x, current_location.y+1),
    [SOUTH] = location(current_location.x, current_location.y-1),
    [EAST] = location(current_location.x+1, current_location.y),
    [WEST] = location(current_location.x-1, current_location.y)
  };
  enum dir_t d;
  for (int i = 0; i < MAX_DIRS; i++) {
    if (location_equal(adj_tiles[i], l)) {
      d = i;
      break;
    }
  }
  d = dir_opposite(d);
  return tile_draft(d, available_tiles);
}

struct location_t select_location(struct location_t* possible_locations, int length)
{
  printf("Between:\n");
  for (int i = 0; i < length; i++) {
    printf("%d:(%d,%d)\t", i+1,  possible_locations[i].x, possible_locations[i].y);
    if ((i+1)%5 == 0 || i == length-1) printf("\n");
  }
    
  printf("Choose the location (1-%d)\n", length);
  int choice = rand()%length;
  printf(">> I choose %d:(%d,%d)\n", choice+1,  possible_locations[choice].x, possible_locations[choice].y);
  
  return possible_locations[choice];
}

struct tile_t* select_tile(struct tile_t** available_tiles, int length)
{
  printf("Between:\n");
  for (int i = 0; i < length; i++) {
    printf("%d: %s\t", i+1, tile_name(available_tiles[i]));
    if ((i+1)%5 == 0 || i == length-1) printf("\n");
  }
      
  printf("Choose the tile (1-%d)\n", length);
  int choice = rand()%length;
  printf(">> I choose %d: %s\n", choice+1, tile_name(available_tiles[choice]));
  
  return available_tiles[choice];
}

void place_tile(struct location_t l, struct tile_t* tile, struct game_state_t* game_state)
{
  game_state->board[l.x][l.y] = tile;
}

int list_open_location(struct location_t* possible_locations, struct game_state_t* game_state)
{
  struct location_t current_location = game_state->current_location;
  int i = 0;    

  struct location_t adj_tiles[MAX_DIRS] = {
    [NORTH] = location(current_location.x, current_location.y+1),
    [SOUTH] = location(current_location.x, current_location.y-1),
    [EAST] = location(current_location.x+1, current_location.y),
    [WEST] = location(current_location.x-1, current_location.y)
  };
  for (int d = 0; d < MAX_DIRS; d++) {
    if (tile_can_open(location_to_tile(current_location, game_state), d)) {
      if (location_is_valid(adj_tiles[d]) && !tile_is_empty(location_to_tile(adj_tiles[d], game_state))) {
        if (tile_can_open(location_to_tile(adj_tiles[d], game_state), dir_opposite(d))) {
          possible_locations[i] = adj_tiles[d];
          i ++;
        }
      }
    }
  }
  return i;
}

void move_player(struct location_t l, struct game_state_t* game_state)
{
  game_state->current_location = l;
}
