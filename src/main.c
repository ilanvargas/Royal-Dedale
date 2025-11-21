#include <stdio.h>
#include "game.h"

int main()
{
    init_tiles(0);
    init_state(&game_state);
    int current_turn = 1;
    struct location_t* possible_locations; 
    while (current_turn <= MAX_TURNS && !exit_reached(&game_state))
    {
        int num_possible_locations = list_empty_locations_with_finite_opening_cost(possible_locations, &game_state);
        if (!location_is_valid(possible_locations[0]) && decide_to_place_tile())
        {
            
            struct location_t selected_location = select_location(possible_locations, num_possible_locations);
            struct tile_t* available_tiles[NUM_TILES_PER_TURN];
            int num_available_tiles = generate_some_tiles(selected_location, available_tiles, &game_state);
            struct tile_t* selected_tile = select_tile(available_tiles, num_available_tiles);
            place_tile(selected_location, selected_tile, &game_state);
        }
        else
        {
            int num_possible_locations2 = list_open_location(possible_locations, &game_state);
            struct location_t selected_location = select_location(possible_locations, num_possible_locations2);
            move_player(selected_location, &game_state);
        }
        current_turn++;
    }
    int player_has_won = exit_reached(&game_state);
    printf("%d\n", player_has_won);

    return 0;
}