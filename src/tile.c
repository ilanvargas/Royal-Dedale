#include "tile.h"
#include <stdlib.h>
#include <string.h>

#define MAX_TILE_NAME_LENGTH 40

/** Implementation of the type of tile 
 */

struct tile_t
{
  char name[MAX_TILE_NAME_LENGTH];
  struct stash_t traversal_cost;
  struct stash_t opening_cost[MAX_DIRS];
};

//Basic tile

struct tile_t EMPTY_TILE = {
  .name = "empty",
  .traversal_cost = INFINITE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
  }
};

struct tile_t START_TILE  = {
  .name = "start",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
};

struct tile_t EXIT_TILE = {
  .name = "exit",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
};

//Game tile

struct tile_t CLOISTER_TILE = {
  .name = "cloister",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t N_TERRACE_TILE = {
  .name = "n terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t E_TERRACE_TILE = {
  .name = "e terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t W_TERRACE_TILE = {
  .name = "w terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t S_TERRACE_TILE = {
  .name = "s terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t EW_CORRIDOR_TILE = {
  .name = "ew corridor",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t NS_CORRIDOR_TILE = {
  .name = "ns corridor",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t* p_tiles[] = {
  &EMPTY_TILE,
  &START_TILE,
  &EXIT_TILE,
  &CLOISTER_TILE,
  &N_TERRACE_TILE,
  &E_TERRACE_TILE,
  &W_TERRACE_TILE,
  &S_TERRACE_TILE,
  &EW_CORRIDOR_TILE,
  &NS_CORRIDOR_TILE
};

/** Tiles fonctions
 */

//Array of arrays of tiles that can open for each direction, will be useful for the draft
int p_tiles_direction_length[MAX_DIRS] = {0};
struct tile_t* p_tiles_direction[MAX_DIRS][TILES_NUMBER];

void init_p_tiles_direction()
{
  for (int d = 0; d < MAX_DIRS; d++) {
    for (int i = 0; i < TILES_NUMBER; i++) {
      if (tile_can_open(p_tiles[i], d)) {
        p_tiles_direction[d][p_tiles_direction_length[d]] = p_tiles[i];
        p_tiles_direction_length[d]++;
      }
    }
  }
}

void init_tiles(unsigned int tile_seed)
{
  srand(tile_seed);

  init_p_tiles_direction();
}

const char* tile_name(const struct tile_t* tile)
{
    return tile->name;
}

struct stash_t tile_traversal_cost(const struct tile_t* tile)
{
    return tile->traversal_cost;
}

struct stash_t tile_opening_cost(const struct tile_t* tile, enum dir_t d)
{
    if (d >= MAX_DIRS) return INFINITE_STEP_STASH;
    return tile->opening_cost[d];
}

struct tile_t* tile_generate_empty()
{
  return &EMPTY_TILE;
}

struct tile_t* tile_generate_start()
{
  return &START_TILE;
}

struct tile_t* tile_generate_exit()
{
  return &EXIT_TILE;
}

struct tile_t* tile_generate_by_name(const char* name)
{
  for (int i = 0; i < TILES_NUMBER; i++) {
    if (!strcmp(name, p_tiles[i]->name)) return p_tiles[i]; 
  }
  return &EMPTY_TILE;
}

unsigned int tile_draft(enum dir_t d, struct tile_t** results)
{
  if (d > MAX_DIRS || p_tiles_direction_length[d] == 0) return 0;

  unsigned int c = 0;
  for (int i = 0; i < NUM_TILES_PER_TURN; i++) {
    struct tile_t* p_tile_rand = p_tiles_direction[d][rand()%p_tiles_direction_length[d]];
    
    int is_repeted = 0;
    for (unsigned int j = 0; j < c; j++) {
      if (!strcmp(p_tile_rand->name, results[j]->name)) {
        is_repeted = 1;
        break;
      }
    }
    if (!is_repeted) {
      results[c] = p_tile_rand;
      c++;
    }
  }
  return c;
}

int tile_is_empty(const struct tile_t* tile)
{
  if (tile == &EMPTY_TILE) return 1;
  return 0;
}

int tile_can_open(const struct tile_t* tile, enum dir_t d)
{
  if (tile->opening_cost[d].r[STEP] == UINT_MAX) return 0;
  return 1;
}
