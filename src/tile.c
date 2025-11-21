#include "tiles_in_game.h"
#include <stdlib.h>
#include <string.h>

//Array of arrays of tiles that can open for each direction
// Will be useful for the draft
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
  if (!strcmp(tile->name, "empty")) return 1;
  return 0;
}

int tile_can_open(const struct tile_t* tile, enum dir_t d)
{
  if (tile->opening_cost[d].r[STEP] == UINT_MAX) return 0;
  return 1;
}
