#ifndef __DEDALE_TILE_BIS_H__
#define __DEDALE_TILE_BIS_H__

#include "tile.h"

/** Tile rotation
 */
enum rot_t {
  d0, d90, d180, d270, NB_ROT
};

/** be able to acces a direction from a direction with a rotation
 */
#define DIR_TO_ROT(d, r)  (((d) + (r)) % NB_ROT)

void init_tiles_bis(unsigned int tile_seed);

/** Tile opening cost with rotation taken into account
 */
struct stash_t tile_opening_cost_bis(const struct tile_t* tile, enum dir_t d, enum rot_t r);

/** Tile can open with rotaion taken into account
 */
int tile_can_open_bis(const struct tile_t* tile, enum dir_t d, enum rot_t r);

/** Tile draft with resources and tile rotation
 *
 * The `results` and 'results_rot' array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 */
unsigned int tile_draft_bis(enum dir_t d, struct stash_t resources, struct tile_t** results, enum rot_t* results_rot);

#endif  // __DEDALE_TILE_BIS_H__
