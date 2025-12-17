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
  int weight;
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
  },
  .weight = 0
};

struct tile_t START_TILE  = {
  .name = "start",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  },
  .weight = 0
};

#define FINAL_RESOURCE_STASH \
  (struct stash_t) {   \
    .r = {[NUM_RESOURCES] = 1, [NUM_RESOURCES-1] = 1, [NUM_RESOURCES-2] = 1}  \
  }

struct tile_t EXIT_TILE = {
  .name = "exit",
  .traversal_cost = FINAL_RESOURCE_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  },
  .weight = 0
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
  },
  .weight = 2
};

struct tile_t TERRACE_TILE = {
  .name = "terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
  },
  .weight = 1
};

struct tile_t CORRIDOR_TILE = {
  .name = "corridor",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
  },
  .weight = 1
};

struct tile_t* p_tiles[] = {
  &CLOISTER_TILE,
  &TERRACE_TILE,
  &CORRIDOR_TILE,
};

#define TILES_NUMBER 3

/** Tiles fonctions
 */

//Array of arrays of tiles that can open for each direction, will be useful for the draft
int p_tiles_direction_length[MAX_DIRS] = {0};
struct tile_t* p_tiles_direction[MAX_DIRS][TILES_NUMBER*2];

void init_p_tiles_direction()
{
  for (int d = 0; d < MAX_DIRS; d++) {
    for (int i = 0; i < TILES_NUMBER; i++) {
      if (tile_can_open(p_tiles[i], d)) {
        for (int j = 0; j < p_tiles[i]->weight; j++) {
          p_tiles_direction[d][p_tiles_direction_length[d]] = p_tiles[i];
          p_tiles_direction_length[d]++;
        }
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
    struct tile_t* p_tile_rand = (d != INVALID_DIR) 
      ? p_tiles_direction[d][rand()%p_tiles_direction_length[d]] 
      : p_tiles[rand()%TILES_NUMBER];

    results[c] = p_tile_rand;
    c++;
  }
  return c;
}

unsigned int tile_draft_with_resources(enum dir_t d, struct stash_t resources, struct tile_t** results)
{
  unsigned int c = 0;
  for (int i = 0; i < NUM_TILES_PER_TURN; i++) {
    struct tile_t* p_tile_rand = (d != INVALID_DIR) 
      ? p_tiles_direction[d][rand()%p_tiles_direction_length[d]] 
      : p_tiles[rand()%TILES_NUMBER];
    if (stash_contains(&resources, &p_tile_rand->opening_cost[d])) {}
    int is_repeted = 0;
    for (unsigned int j = 0; j < c; j++) {
      if ((struct tile_t*)p_tile_rand == (struct tile_t*)results[j]) {
        is_repeted = 1;
        break;
      }
    }
    struct stash_t op = p_tile_rand->opening_cost[d];
    if (!is_repeted && stash_contains(&resources, &op)) {
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
  if (tile_opening_cost(tile, d).r[STEP] == UINT_MAX) return 0;
  return 1;
}
