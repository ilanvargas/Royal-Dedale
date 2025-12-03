#ifndef __DEDALE_TUI_H__
#define __DEDALE_TUI_H__

#include "location.h"
#include "game.h"

void init_tui(int is_iterative);

/** Place a new tile on the tui
 */
void tui_place_tile(int is_iterative, struct location_t l, struct tile_t* tile);

/** Move the player from he's old position to his new one on the tui
 *
 * Call this function before moving the player
 */
void tui_move_player(int is_iterative, struct location_t l, struct game_state_t* game_state);

/** Print the tui board representation
 */
void tui_print(int is_iterative);

#endif //__DEDALE_TUI_H__
