#include "tile_bis.h"
#include <stdlib.h>

void init_tiles_bis(unsigned int tile_seed)
{
  srand(tile_seed);
}

struct stash_t tile_opening_cost_bis(const struct tile_bis_t tile, enum dir_t d)
{
  return tile_opening_cost(tile.tile, DIR_TO_ROT(d, tile.rot));
}

int tile_can_open_bis(const struct tile_bis_t tile, enum dir_t d)
{
  return tile_can_open(tile.tile, DIR_TO_ROT(d, tile.rot));
}

unsigned int tile_draft_bis(enum dir_t d, struct stash_t resources, struct tile_bis_t* results)
{
  struct tile_t* results1[NUM_TILES_PER_TURN];
  unsigned int c1 = tile_draft(d, results1);

  struct tile_t* results2[NUM_TILES_PER_TURN];
  unsigned int c2 = tile_draft(INVALID_DIR, results2);

  unsigned int c = 0;

  for (unsigned int i = 0; i < c1; i++) {
    struct stash_t cost_to_open = tile_opening_cost(results1[i], d);
    if (stash_contains(&resources, &cost_to_open)) {
      int is_repeted = 0;
      for (unsigned int j = 0; j < c; j++) {
        if (results1[i] == results[j].tile) {
          is_repeted = 1;
          break;
        }
      }
      if (!is_repeted) {
        results[c].tile = results1[i];
        results[c].rot = d0;
        c++;
      }
    }
  } 

  for (unsigned int i = 0; i < c2; i++) {
    enum rot_t rot_rand = rand()%NB_ROT;
    struct stash_t cost_to_open = tile_opening_cost(results2[i], DIR_TO_ROT(d, rot_rand));
    if (tile_can_open(results2[i], DIR_TO_ROT(d, rot_rand)) && stash_contains(&resources, &cost_to_open)) {
      int is_repeted = 0;
      for (unsigned int j = 0; j < c; j++) {
        if (results2[i] == results[j].tile && rot_rand == results[j].rot) {
          is_repeted = 1;
          break;
        }
      }
      if (!is_repeted) {
        results[c].tile = results2[i];
        results[c].rot = rot_rand;
        c++;
      }
    }
  } 
  return c;
}

