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
  if (strcmp(name, "start")) return &START_TILE;
  if (strcmp(name, "exit")) return &EXIT_TILE;
  if (strcmp(name, "cloister")) return &CLOISTER_TILE;
  if (strcmp(name, "n terrace")) return &N_TERRACE_TILE;
  if (strcmp(name, "s terrace")) return &S_TERRACE_TILE;
  if (strcmp(name, "e terrace")) return &E_TERRACE_TILE;
  if (strcmp(name, "w terrace")) return &W_TERRACE_TILE;
  if (strcmp(name, "ew corridor")) return &EW_CORRIDOR_TILE;
  if (strcmp(name, "ns corridor")) return &NS_CORRIDOR_TILE;
  return &EMPTY_TILE;
}
/*
unsigned int tile_draft(enum dir_t d, struct tile_t** results)
{
  unsigned int c = 0;
  int i = 0;
  while (i < NUM_TILES_PER_TURN)
  {
    int r = rand() % TILES_NUMBER;
    struct tile_t* random_tile = tile_generate_by_name(tiles_name[r]);
    if (tile_can_open(random_tile, d) )
    {
      results[i] = &random_tile;
      c++;
      i++;
    }

  }
  return c;
}
*/
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
