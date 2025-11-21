#include "game.h"

void init_state(struct game_state_t* game_state)
{
  game_state->steps = INFINITE_STEP_STASH;
  
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      game_state->board[i][j] = tile_generate_empty();
    }
  }
  game_state->board[0][0] = tile_generate_start();
  game_state->board[BOARD_WIDTH-1][BOARD_HEIGHT-1] = tile_generate_exit();

  game_state->current_location = location(0, 0);
}

int exit_reached(struct game_state_t* game_state)
{
  if (tile_generate_exit() == game_state->board[game_state->current_location.x][game_state->current_location.y])
    return 1;
  return 0;
}
