#include <stdio.h>
#include "game.h"

struct game_state_t game_state;

int main()
{
    init_tiles(0);
    init_state(0, &game_state);
    int current_turn = 1;

    struct location_t possible_locations[BOARD_SIZE]; 
    struct tile_t* available_tiles[NUM_TILES_PER_TURN];

    int is_player_won = exit_reached(&game_state);
    while (current_turn <= MAX_TURNS && !is_player_won)
    {
        int num_possible_locations = list_empty_locations_with_finite_opening_cost(possible_locations, &game_state);
        if (current_turn == 1 || (num_possible_locations && decide_to_place_tile()))
        {
            printf("Place your tile\n");
            struct location_t selected_location = select_location(possible_locations, num_possible_locations);
            int num_available_tiles = generate_some_tiles(selected_location, available_tiles, &game_state);
            struct tile_t* selected_tile = select_tile(available_tiles, num_available_tiles);
            place_tile(selected_location, selected_tile, &game_state);
        }
        else
        {
            printf("Move the player\n");
            int num_possible_locations = list_open_location(possible_locations, &game_state);
            struct location_t selected_location = select_location(possible_locations, num_possible_locations);
            move_player(selected_location, &game_state);
        }
        current_turn++;
        is_player_won = exit_reached(&game_state);
    }

    if (is_player_won)
      printf("Congratulations!!!\n");
    else
      printf("You lost :(\n");

    return 0;
}
