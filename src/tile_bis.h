/** Tile draft with tile rotation
 *
 * The `results` and 'results_rot' array must be allocated before calling the function, and
 * able to contain at least `NUM_TILES_PER_TURN` elements.
 *
 */
unsigned int tile_draft(enum dir_t d, struct tile_t** results, int results_rot*);
