#include "tui.h"
#include <stdio.h>

#define CELL_WIDTH 10
#define CELL_HEIGHT 5
#define BOARD_WIDTH_TUI  (BOARD_WIDTH * CELL_WIDTH  + 1)
#define BOARD_HEIGHT_TUI (BOARD_HEIGHT * CELL_HEIGHT + 1)

#define X_TUI(_x) ((_x) * CELL_WIDTH)
#define Y_TUI(_y) ((BOARD_HEIGHT - (_y)) * CELL_HEIGHT)

static char board_tui[BOARD_HEIGHT_TUI][BOARD_WIDTH_TUI];

// Writing the walls of the tiles on the board

void tui_opened_horizontal(struct location_t l)
{
  int x = X_TUI(l.x);
  int y = Y_TUI(l.y);

  board_tui[y][x] = '+';
  if (board_tui[y][x + 1] == '~') {
    for (int i = 1; i < CELL_WIDTH; i++) {
      board_tui[y][x + i] = ' ';
    }
  }
  board_tui[y][x + CELL_WIDTH] = '+';
}

void tui_closed_horizontal(struct location_t l)
{
  int x = X_TUI(l.x);
  int y = Y_TUI(l.y);

  board_tui[y][x] = '+';
  for (int i = 1; i < CELL_WIDTH; i++) {
    board_tui[y][x + i] = '-';
  }
  board_tui[y][x + CELL_WIDTH] = '+';
}

void tui_opened_vertical(struct location_t l)
{
  int x = X_TUI(l.x);
  int y = Y_TUI(l.y);

  board_tui[y - CELL_HEIGHT][x] = '+';  
  if (board_tui[y - CELL_HEIGHT + 1][x] == '~') {
    for (int i = 1; i < CELL_HEIGHT; i++) {
      board_tui[y - CELL_HEIGHT + i][x] = ' ';
    }
  }
  board_tui[y][x] = '+'; 
}

void tui_closed_vertical(struct location_t l)
{
  int x = X_TUI(l.x);
  int y = Y_TUI(l.y);

  board_tui[y - CELL_HEIGHT][x] = '+';  
  for (int i = 1; i < CELL_HEIGHT; i++) {
    board_tui[y - CELL_HEIGHT + i][x] = '|';
  }
  board_tui[y][x] = '+';  
}

// Fonctions public

void init_tui(int is_graphic)
{
  if (is_graphic) {
    for (int r = 0; r < BOARD_HEIGHT_TUI; r++) {
      for (int c = 0; c < BOARD_WIDTH_TUI; c++) {
          board_tui[r][c] = '~';
      }
    }

    tui_opened_horizontal(location(0, 0)); 
    tui_opened_horizontal(location(0, 1)); 
    tui_opened_vertical(location(0, 0)); 
    tui_opened_vertical(location(1, 0)); 

    int x0 = X_TUI(0);
    int y0 = Y_TUI(0) - CELL_HEIGHT;
    for(int i = 1; i < CELL_HEIGHT; i++){
      for(int j = 1; j < CELL_WIDTH; j++){
          board_tui[y0 + i][x0 + j] = ' ';
      }
    }

    int x = BOARD_WIDTH - 1;
    int y = BOARD_HEIGHT - 1;
    tui_opened_horizontal(location(x, y)); 
    tui_opened_horizontal(location(x, y + 1));
    tui_opened_vertical(location(x, y)); 
    tui_opened_vertical(location(x + 1, y)); 

    int x1 = X_TUI(x);
    int y1 = Y_TUI(y) - CELL_HEIGHT;
    for(int i = 1; i < CELL_HEIGHT; i++){
      for(int j = 1; j < CELL_WIDTH; j++){
          board_tui[y1 + i][x1 + j] = ' ';
      }
    }

    int px = X_TUI(0) + CELL_WIDTH / 2;
    int py = Y_TUI(0) - CELL_HEIGHT / 2;
    board_tui[py][px] = 'o';
  }
}

void tui_place_tile(int is_graphic, struct location_t l, struct tile_t* tile)
{
  if (is_graphic) {
    int x0 = X_TUI(l.x);
    int y0 = Y_TUI(l.y) - CELL_HEIGHT;

    for(int i = 1; i < CELL_HEIGHT; i++){
      for(int j = 1; j < CELL_WIDTH; j++){
          board_tui[y0 + i][x0 + j] = ' ';
      }
    }

    if (tile_can_open(tile, NORTH))
      tui_opened_horizontal(location(l.x, l.y + 1));
    else
        tui_closed_horizontal(location(l.x, l.y + 1));

    if (tile_can_open(tile, EAST))
      tui_opened_vertical(location(l.x + 1, l.y));
    else
        tui_closed_vertical(location(l.x + 1, l.y));

    if (tile_can_open(tile, SOUTH))
      tui_opened_horizontal(location(l.x, l.y));
    else
        tui_closed_horizontal(location(l.x, l.y));

    if (tile_can_open(tile, WEST))
      tui_opened_vertical(location(l.x, l.y));
    else
      tui_closed_vertical(location(l.x, l.y));
  }
}

void tui_move_player(int is_graphic, struct location_t l, struct game_state_t* game_state)
{
  if (is_graphic) {
    int old_px = X_TUI(game_state->current_location.x) + CELL_WIDTH / 2;
    int old_py = Y_TUI(game_state->current_location.y) - CELL_HEIGHT / 2;  // CHANGÉ: - au lieu de +
    board_tui[old_py][old_px] = ' ';

    int new_px = X_TUI(l.x) + CELL_WIDTH / 2;
    int new_py = Y_TUI(l.y) - CELL_HEIGHT / 2; 
    board_tui[new_py][new_px] = 'o';
  }
}

void tui_print(int is_graphic)
{
  if (is_graphic) {
    for (int i = 0; i < BOARD_HEIGHT_TUI; i++) {
      for (int j = 0; j < BOARD_WIDTH_TUI; j++) {
          printf("%c",board_tui[i][j]);
      }
      printf("\n");
    }
  }
}
