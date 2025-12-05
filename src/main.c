#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include "game.h"
#include "tui.h"
#include <stdlib.h>

struct game_state_t game_state;

int main(int argc, char* argv[])
{
    unsigned int s = 0;
    unsigned int t = 0;
    unsigned int n = 100;
    int is_iterative = 0;
    int is_graphic = 0;

    int opt;
    while ((opt = getopt(argc, argv, "s:t:n:ig")) != -1)
    {
      switch (opt)
      {
        case 's':
          s = atoi(optarg);
          break;
        case 't':
          t = atoi(optarg);
          break;
        case 'n':
          n = atoi(optarg);
          break;
        case 'i':
          is_iterative = 1;
          break;
        case 'g':
          is_graphic = 1;
          break;
      }
    }
    init_tiles(t);
    init_state(s, &game_state);
    init_tui(is_graphic);
    unsigned int current_turn = 1;

    struct location_t possible_locations[BOARD_SIZE]; 
    struct tile_t* available_tiles[NUM_TILES_PER_TURN*2];
    enum rot_t available_tiles_rot[NUM_TILES_PER_TURN*2];
    int is_player_won = exit_reached(&game_state);
    while (current_turn <= n && !is_player_won && game_state.steps.r[STEP] > 0)
    {
        printf("\e[1mTurn number %d out of %d\e[0m\n", current_turn, n);
        int num_possible_locations = list_empty_locations_with_finite_opening_cost(possible_locations, &game_state);
        if (current_turn == 1 || (num_possible_locations && decide_to_place_tile(is_iterative)))
        {
            printf("Place your tile\n");
            struct location_t selected_location = select_location(is_iterative, possible_locations, num_possible_locations);
            
            enum dir_t d = location_to_dir(selected_location, &game_state);
            int num_available_tiles = tile_draft_bis(dir_opposite(d), available_tiles, available_tiles_rot);
            struct tile_t* selected_tile = select_tile(is_iterative, available_tiles, available_tiles_rot, num_available_tiles);
            place_tile(selected_location, d, selected_tile, &game_state);
            
            tui_place_tile(is_graphic, selected_location, selected_tile);
        }
        else
        {
            printf("Move the player\n");
            int num_possible_locations = list_open_location(possible_locations, &game_state);
            
            struct location_t selected_location = select_location(is_iterative, possible_locations, num_possible_locations);
            tui_move_player(is_graphic, selected_location, &game_state);
            move_player(selected_location, &game_state);
        }
        current_turn++;
        tui_print(is_graphic);
        is_player_won = exit_reached(&game_state);
    }
    if (!game_state.steps.r[STEP])
      printf("No more resources :(\n");
    if (is_player_won)
      printf("Congratulations!!! You found the exit\n");
    else
      printf("You lost :(\n");
    return 0;
}
