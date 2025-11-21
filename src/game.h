#ifndef __DEDALE_GAME_H__
#define __DEDALE_GAME_H__

#include "tile.h"
#include "location.h"

struct game_state_t {
  int steps;
  struct tile_t* board[BOARD_HEIGHT][BOARD_WIDTH];
  struct location_t current_location;
};
struct game_state_t game_state;

void init_state();

int exit_reached(struct game_state_t* game_state);

void list_empty_locations_with_finite_opening_cost(struct location_t* possible_locations, struct game_state_t* game_state);

int decide_to_place_tile();

struct location select_location(struct location_t* possible_locations);

struct tile_t* select_tile(struct tile_t** tiles);

void place_tile(struct location, struct tile_t* tile, struct game_state_t* game_state);

void list_open_location(struct location_t* possible_locations, struct game_state_t* game_state);

void move_player(struct location_t location, struct game_state_t* game_state);

#endif //__DEDALE_GAME_H__
