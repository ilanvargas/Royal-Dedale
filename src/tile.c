#include "tile.h"
#include <stdlib.h>

struct tile_t
{
    char *name;
    struct stash_t traversal_cost;
    struct stash_t opening_cost[MAX_DIRS];
};

//Tiles game
struct tile_t CLOISTER = {.name = "cloister,
                            

void init_tiles(unsigned int tile_seed)
{
  srand(tile_seed);
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
  struct tile_t tile = {.name = ""};
  for (int i = 0; i < MAX_DIRS; i++)
    tile.opening_cost[i] = INFINITE_STEP_STASH;

  return tile
}

struct tile_t* tile_generate_start();
{
  struct tile_t tile = {
    .name = "start",      
    .traversal_cost = ONE_STEP_STASH,
    };
  for (int i = 0; i < MAX_DIRS; i++)
    tile.opening_cost[i] = ONE_STEP_STASH;

  return tile
}

struct tile_t* tile_generate_exit();
{
  struct tile_t tile = {
    .name = "exit",      
    .traversal_cost = ONE_STEP_STASH,
    };
  for (int i = 0; i < MAX_DIRS; i++)
    tile.opening_cost[i] = ONE_STEP_STASH;

  return tile
}

struct tile_t* tile_generate_by_name(const char* name);

unsigned int tile_draft(enum dir_t d, struct tile_t** results);

int tile_is_empty(const struct tile_t* tile)
{
  if (!name[0]) return 1;
  return 0;
}

int tile_can_open(const struct tile_t* tile, enum dir_t d)
{
  if (tile->opening_cost[d].r[STEP] == UINT_MAX) return 0;
  return 1;
}
