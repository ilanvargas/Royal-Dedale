#include "tile.h"
#include "tiles_in_game.h"
#include <stdlib.h>
#include <string.h>

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
  if (str_cmp(name, "start")) return &START_TILE_;
  if (str_cmp(name, "exit")) return &EXIT_TILE;
  if (str_cmp(name, "cloister")) return &CLOISTER_TILE;
  if (str_cmp(name, "n terrace")) return &N_TERRACE_TILE;
  if (str_cmp(name, "s terrace")) return &S_TERRACE_TILE;
  if (str_cmp(name, "e terrace")) return &E_TERRACE_TILE;
  if (str_cmp(name, "w terrace")) return &W_TERRACE_TILE;
  if (str_cmp(name, "ew corridor")) return &EW_CORRIDOR_TILE;
  if (str_cmp(name, "ns corridor")) return &NS_CORRIDOR_TILE;
}

unsigned int tile_draft(enum dir_t d, struct tile_t** results);

int tile_is_empty(const struct tile_t* tile)
{
  if (strcmp(tile->name, "empty")) return 1;
  return 0;
}

int tile_can_open(const struct tile_t* tile, enum dir_t d)
{
  if (tile->opening_cost[d].r[STEP] == UINT_MAX) return 0;
  return 1;
}
