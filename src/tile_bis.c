#include "tile_bis.h"
#include <stdlib.h>

struct tile_t
{
  char name[MAX_TILE_NAME_LENGTH];
  struct stash_t traversal_cost;
  struct stash_t opening_cost[MAX_DIRS];
  int weight;
};

void init_tiles_bis(unsigned int tile_seed)
{
  srand(tile_seed);
}

struct stash_t tile_opening_cost_bis(const struct tile_t* tile, enum dir_t d, enum rot_t r)
{
  return tile_opening_cost(tile, DIR_TO_ROT(d,r));
}

int tile_can_open_bis(const struct tile_t* tile, enum dir_t d, enum rot_t r)
{
  return tile_can_open(tile, DIR_TO_ROT(d,r));
}

unsigned int tile_draft_bis(enum dir_t d, struct stash_t resources, struct tile_t** results, enum rot_t* results_rot)
{
  struct tile_t* results1[NUM_TILES_PER_TURN];
  unsigned int c1 = tile_draft(d, results1);

  struct tile_t* results2[NUM_TILES_PER_TURN];
  unsigned int c2 = tile_draft(INVALID_DIR, results2);

  unsigned int c = 0;

  for (unsigned int i = 0; i < c1; i++) {
    struct stash_t cost_to_open = tile_opening_cost_bis(results1[i], d, d0);
    if (stash_contains(&resources, &cost_to_open)) {
      int is_repeted = 0;
      for (unsigned int j = 0; j < c; j++) {
        if ((struct tile_t*)results1[i] == (struct tile_t*)results[j]) {
          is_repeted = 1;
          break;
        }
      }
      if (!is_repeted) {
        results[c] = results1[i];
        results_rot[c] = d0;
        c++;
      }
    }
  } 

  for (unsigned int i = 0; i < c2; i++) {
    enum rot_t rot_rand = rand()%NB_ROT;
    struct stash_t cost_to_open = tile_opening_cost_bis(results2[i], d, rot_rand);
    if (tile_can_open(results2[i], DIR_TO_ROT(d, rot_rand)) && stash_contains(&resources, &cost_to_open)) {
      int is_repeted = 0;
      for (unsigned int j = 0; j < c; j++) {
        if ((struct tile_t*)results2[i] == (struct tile_t*)results[j] && rot_rand == results_rot[j]) {
          is_repeted = 1;
          break;
        }
      }
      if (!is_repeted) {
        results[c] = results2[i];
        results_rot[c] = rot_rand;
        c++;
      }
    }
  } 
  return c;
}

