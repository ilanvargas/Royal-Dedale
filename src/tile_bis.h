#ifndef __DEDALE_TILE_BIS_H__
#define __DEDALE_TILE_BIS_H__

/** Tile rotation
 */
enum rot_t {
  d0, d90, d180, d270, NB_ROT
};

/** Tile draft with resources and tile rotation
 *
 * The `results` and 'results_rot' array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 */
unsigned int tile_draft_bis(enum dir_t d, struct stash_t resources, struct tile_t** results, enum rot_t* results_rot);

/** Change the rotation of a tile
 *
 * It's importaant to note that you are changing all tiles of type 'tile' and it will be probably
 * changed again in the program
 *
 * Always call this function befora verifing if a tile can open in a direction
 */
void change_tile_rot(struct tile_t* tile, enum rot_t r);

/** Gives tile rotation in the struct
 */
enum rot_t tile_rot(struct tile_t* tile);

#endif  // __DEDALE_TILE_BIS_H__
