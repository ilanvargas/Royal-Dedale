#include "game.h"
#include <stdio.h>
#include <stdlib.h>

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
  struct tile_t* current_tile = location_to_tile(current_location, game_state);
  int i = 0;    

  struct location_t adj_tiles[MAX_DIRS] = {
    [NORTH] = location(current_location.x, current_location.y+1),
    [SOUTH] = location(current_location.x, current_location.y-1),
    [EAST] = location(current_location.x+1, current_location.y),
    [WEST] = location(current_location.x-1, current_location.y)
  };
  for (int d = 0; d < MAX_DIRS; d++) {
    if (tile_can_open_bis(current_tile, d, game_state->board_rot[current_location.x][current_location.y])) {
      if (location_is_valid(adj_tiles[d]) && tile_is_empty(location_to_tile(adj_tiles[d], game_state))) {
        possible_locations[i] = adj_tiles[d];
        i ++;
      }
    }
  }
  return i;
}

int decide_to_place_tile(int is_iterative)
{
  if (!is_iterative)
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
  else
  {
    char choice;
    while (1) {
      printf("Do you want to place or move? (p/m)\n");
      scanf("%c", &choice);
      switch (choice) {
        case 'p':
          return 1;
        case 'm':
          return 0;
        default:
          break;
      }
    }
  }
}

enum dir_t location_to_dir(struct location_t l, struct game_state_t* game_state)
{
  struct location_t current_location = game_state->current_location;
  if (!location_is_adjacent(l, current_location)) return 0;

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
  return d;
}

struct location_t select_location(int is_iterative, struct location_t* possible_locations, int length)
{
  if (!is_iterative)
  {
    printf("Between:\n");
    for (int i = 0; i < length; i++) {
      printf("%d:(%d,%d)\t", i+1,  possible_locations[i].x, possible_locations[i].y);
    }
    printf("\n");
      
    printf("Choose the location (1-%d)\n", length);
    int choice = rand()%length;
    printf(">> I choose %d:(%d,%d)\n", choice+1,  possible_locations[choice].x, possible_locations[choice].y);
    
    return possible_locations[choice];
  }
  else
  {
    printf("Between:\n");
    for (int i = 0; i < length; i++) {
      printf("%d:(%d,%d)\t", i+1,  possible_locations[i].x, possible_locations[i].y);
    }
    printf("\n");
  
    int i;
    printf("Choose the location (1-%d)\n", length);
    scanf("%d", &i);
    return possible_locations[i-1];
  }
}

void pay_opening_cost(struct location_t l, enum dir_t d, struct game_state_t* game_state)
{
  struct stash_t a = game_state->steps;
  struct stash_t b = tile_opening_cost(location_to_tile(l, game_state),dir_opposite(d));
  game_state->steps = stash_sub(&a, &b);
}

void pay_traversal_cost(struct game_state_t* game_state)
{
  struct location_t l = game_state->current_location;
  struct stash_t a = game_state->steps;
  struct stash_t b = tile_traversal_cost(location_to_tile(l, game_state));
  game_state->steps = stash_sub(&a, &b);
}

struct tile_t* select_tile(int is_iterative, struct tile_t** available_tiles, enum rot_t* available_tiles_rot, int length)
{
  if (!is_iterative)
  {
    printf("Between:\n");
    for (int i = 0; i < length; i++) {
      printf("%d: %s\t", i+1, tile_name(available_tiles[i]));
    }
    printf("\n");
    printf("Choose the tile (1-%d)\n", length);
    int choice = rand()%length;
    printf(">> I choose %d: %s\n", choice+1, tile_name(available_tiles[choice]));

    change_tile_rot(available_tiles[choice], available_tiles_rot[choice]);
    return available_tiles[choice];
  }
  else
  {
    printf("Between:\n");
    for (int i = 0; i < length; i++) {
      printf("%d: %s\t", i+1, tile_name(available_tiles[i]));
      if ((i+1)%5 == 0 || i == length-1) printf("\n");
    }
    int i;
    printf("Choose the tile (1-%d)\n", length);
    scanf("%d", &i);
    change_tile_rot(available_tiles[i-1], available_tiles_rot[i-1]);
    return available_tiles[i-1]; 
  }
}

void place_tile(struct location_t l, enum dir_t d, struct tile_t* tile, struct game_state_t* game_state)
{
  game_state->board[l.x][l.y] = tile;
  game_state->board_rot[l.x][l.y] = tile_rot(tile);
  pay_opening_cost(l, d, game_state);
}

int list_open_location(struct location_t* possible_locations, struct game_state_t* game_state)
{
  struct location_t current_location = game_state->current_location;
  struct tile_t* current_tile = location_to_tile(current_location, game_state);
  int i = 0;    

  struct location_t adj_tiles[MAX_DIRS] = {
    [NORTH] = location(current_location.x, current_location.y+1),
    [SOUTH] = location(current_location.x, current_location.y-1),
    [EAST] = location(current_location.x+1, current_location.y),
    [WEST] = location(current_location.x-1, current_location.y)
  };
  for (int d = 0; d < MAX_DIRS; d++) {
    change_tile_rot(current_tile, game_state->board_rot[current_location.x][current_location.y]);
    if (tile_can_open(current_tile, d)) {
      if (location_is_valid(adj_tiles[d]) && !tile_is_empty(location_to_tile(adj_tiles[d], game_state))) {
        change_tile_rot(location_to_tile(adj_tiles[d], game_state), game_state->board_rot[adj_tiles[d].x][adj_tiles[d].y]);
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
  pay_traversal_cost(game_state);
}


void random_tile_rotation(int is_interactive, struct tile_t* tile, enum dir_t d, int* num_rotations)
{
  return;
  if (!is_interactive) {
    printf("Do you want rotate your tile\n");
    int choice = rand()%3;
    if (choice) {
      printf(">> No\n");
      return ;
    }
    printf(">> Yes\n");
  }
  else {
    char choice;
    printf("Do you want to place or move? (y/n)\n");
    scanf("%c", &choice);
    switch (choice) {
      case 'y':
        break;
      default:
        return;
    }
  }

  enum rot_t rots[NB_ROT-1];
  int rots_len = 0;
  for (int i = 0; i < NB_ROT-1; i++) {
    enum rot_t r = (tile_rot(tile)+1)%NB_ROT;
    if (tile_can_open_bis(tile, d, r)) {
      rots[rots_len] = r;
      rots_len ++;
    }
  }
  if (!rots_len) {
    change_tile_rot(tile, (tile_rot(tile)+1)%NB_ROT);
    return;
  }
  change_tile_rot(tile, rots[rand()%rots_len]);
  *num_rotations -= 1;
  return;
}

