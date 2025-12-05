#ifndef __DEDALE_TILE_BIS_H__
#define __DEDALE_TILE_BIS_H__

/** Tile rotation
 */
enum rot_t;

/** Tile draft with tile rotation
 *
 * The `results` and 'results_rot' array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 *
 */
unsigned int tile_draft_bis(enum dir_t d, struct tile_t** results, enum rot_t* results_rot);

#endif  // __DEDALE_TILE_BIS_H__
