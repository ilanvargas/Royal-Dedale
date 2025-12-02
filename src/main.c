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

    int opt;
    while ((opt = getopt(argc, argv, "s:t:n:i")) != -1)
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
      }
    }
    init_tiles(t);
    init_state(s, &game_state);
    init_tui();
    unsigned int current_turn = 1;

    struct location_t possible_locations[BOARD_SIZE]; 
    struct tile_t* available_tiles[NUM_TILES_PER_TURN];

    int is_player_won = exit_reached(&game_state);
    while (current_turn <= n && !is_player_won)
    {
        printf("\e[1mTurn number %d out of %d\e[0m\n", current_turn, n);
        int num_possible_locations = list_empty_locations_with_finite_opening_cost(possible_locations, &game_state);
        if (current_turn == 1 || (num_possible_locations && decide_to_place_tile(is_iterative)))
        {
            printf("Place your tile\n");
            struct location_t selected_location = select_location(is_iterative, possible_locations, num_possible_locations);
            int num_available_tiles = generate_some_tiles(selected_location, available_tiles, &game_state);
            struct tile_t* selected_tile = select_tile(is_iterative, available_tiles, num_available_tiles);
            place_tile(selected_location, selected_tile, &game_state);
            tui_place_tile(selected_location, selected_tile);
        }
        else
        {
            printf("Move the player\n");
            int num_possible_locations = list_open_location(possible_locations, &game_state);
            struct location_t selected_location = select_location(is_iterative, possible_locations, num_possible_locations);
            tui_move_player(selected_location, &game_state);
            move_player(selected_location, &game_state);
        }
        current_turn++;
        tui_print();
        is_player_won = exit_reached(&game_state);
    }

    if (is_player_won)
      printf("Congratulations!!! You found the exit\n");
    else
      printf("You lost :(\n");

    return 0;
}
