#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


#include "tui.h"
#include "equipement.h"

struct game_state_t game_state;

int main(int argc, char* argv[])
{
    unsigned int s = 0;
    unsigned int t = 0;
    unsigned int n = 100;
    unsigned int equipement_seed = 1;
    int is_interactive = 0;
    int is_graphic = 0;
    int is_base_version = 0;

    int opt;
    while ((opt = getopt(argc, argv, "s:t:n:q:igb")) != -1)
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
        case 'q':
          equipement_seed = atoi(optarg);
          break;
        case 'i':
          is_interactive = 1;
          break;
        case 'g':
          is_graphic = 1;
          break;
        case 'b':
          is_base_version = 1;
          break;
      }
    }

    init_tiles(t);
    init_tiles_bis(t);
    init_state(s, &game_state);
    init_equipement(equipement_seed);
    init_tui(is_graphic);

    unsigned int current_turn = 1;
    int num_rotations = BOARD_WIDTH * BOARD_HEIGHT / 10;

    struct location_t possible_locations[4]; 
    struct tile_bis_t available_tiles[NUM_TILES_PER_TURN*2];
    struct location_t target_locations_sorted[NUM_TARGET_LOCATIONS];

    int is_player_won = exit_reached(&game_state);
    int num_target_locations = sort_target_locations(target_locations_sorted, &game_state);

    // ###---------------- Base version main loop (includes interactive version) ----------------###

    if (is_base_version) 
    {

    while (current_turn <= n && !is_player_won && game_state.steps.r[STEP] > 0)
    {
        printf("\e[1mTurn number %d out of %d\e[0m\n", current_turn, n);
        print_target_locations_sorted(target_locations_sorted, num_target_locations);

        struct stash_t initial_resources = game_state.steps;
        int num_possible_locations = list_empty_locations_with_finite_opening_cost(possible_locations, &game_state);
        if (current_turn == 1 || (num_possible_locations && decide_to_place_tile(is_interactive)))
        {
            printf("Place your tile\n");
            struct location_t selected_location = select_location(is_interactive, possible_locations, num_possible_locations);
            
            enum dir_t d = location_to_dir(selected_location, &game_state);
            int num_available_tiles = tile_draft_bis(dir_opposite(d), game_state.steps, available_tiles);
            struct tile_bis_t selected_tile = select_tile(is_interactive, available_tiles, num_available_tiles);
            random_tile_rotation(is_interactive, selected_tile, d, &num_rotations);
            place_tile(selected_location, d, selected_tile, &game_state);
            can_gain_equipement(&game_state);
            struct stash_t final_resources = game_state.steps;
            struct stash_t gained_resources = stash_sub(&final_resources, &initial_resources);
            
            on_tile_open(&game_state);
            on_resource_gain(&game_state, gained_resources);
            tui_place_tile(is_graphic, selected_location, selected_tile);
        }
        else
        {
            printf("Move the player\n");
            int num_possible_locations = list_open_location(possible_locations, &game_state);
            struct location_t selected_location = select_location(is_interactive, possible_locations, num_possible_locations);
            tui_move_player(is_graphic, selected_location, &game_state);
            move_player(selected_location, &game_state);
            struct stash_t final_resources = game_state.steps;
            struct stash_t gained_resources = stash_sub(&final_resources, &initial_resources);
            
            on_move(&game_state);
            on_resource_gain(&game_state, gained_resources);
        }

        num_target_locations = sort_target_locations(target_locations_sorted, &game_state);
        current_turn++;
        tui_print(is_graphic);
        is_player_won = exit_reached(&game_state);
        printf("\n");
      }

      }

    // ###---------------- Main loop version with path finder algoritm to target ----------------###

    else
    {

    struct location_t path_to_target[BOARD_SIZE];
    int is_game_over = 0;

    while(!is_game_over)
    {
        struct location_t target_location_near = (num_target_locations > 0) ? target_locations_sorted[0] : location(BOARD_WIDTH-1, BOARD_HEIGHT-1);
        unsigned int path_to_target_len = path_target_finder(target_location_near, &game_state, path_to_target);
        if (path_to_target_len >= BOARD_SIZE) { // the path has been blocked by unopening tiles
            printf("You have blocked yourself, you cannot reach your next objective. The game is unwinable\n");
            target_location_near = game_state.current_location;
            is_game_over = 1;
        }
        
        unsigned int i = 1;
        while(i < path_to_target_len && !tile_is_empty(location_to_tile(path_to_target[i], &game_state).tile) && !is_game_over) {
            struct stash_t initial_resources = game_state.steps;
            printf("\e[1mTurn number %d out of %d\e[0m\n", current_turn, n);
            print_target_locations_sorted(target_locations_sorted, num_target_locations);
            print_path_target(path_to_target, path_to_target_len, target_location_near);
            struct location_t selected_location = path_to_target[i];
            printf(">> Move the player to the location (%d,%d)\n", selected_location.x, selected_location.y);

            tui_move_player(is_graphic, selected_location, &game_state);
            move_player(selected_location, &game_state);
            target_location_reached(&game_state);
            struct stash_t final_resources = game_state.steps;
            struct stash_t gained_resources = stash_sub(&final_resources, &initial_resources);
            on_move(&game_state);
            on_resource_gain(&game_state, gained_resources);
            i++;

            current_turn++;
            tui_print(is_graphic);
            is_player_won = exit_reached(&game_state);
            printf("\n");

            if (current_turn > n || is_player_won || game_state.steps.r[STEP] <= 0) is_game_over = 1;
        }
        if (i < path_to_target_len && !is_game_over) {
            struct stash_t initial_resources2 = game_state.steps;
            printf("\e[1mTurn number %d out of %d\e[0m\n", current_turn, n);
            print_target_locations_sorted(target_locations_sorted, num_target_locations);
            print_path_target(path_to_target, path_to_target_len, target_location_near);
            struct location_t selected_location = path_to_target[path_to_target_len-1];
            printf(">> Place tile in the location (%d,%d)\n", selected_location.x, selected_location.y);
            
            enum dir_t d = location_to_dir(selected_location, &game_state);
            int num_available_tiles = tile_draft_bis(dir_opposite(d), game_state.steps, available_tiles);
            struct tile_bis_t selected_tile = select_tile(0, available_tiles, num_available_tiles);
            random_tile_rotation(0, selected_tile, d, &num_rotations);
            place_tile(selected_location, d, selected_tile, &game_state);
            can_gain_equipement(&game_state);
            struct stash_t final_resources = game_state.steps;
            struct stash_t gained_resources = stash_sub(&final_resources, &initial_resources2);
            on_tile_open(&game_state);
            on_resource_gain(&game_state, gained_resources);
            tui_place_tile(is_graphic, selected_location, selected_tile);

            current_turn++;
            tui_print(is_graphic);
            is_player_won = exit_reached(&game_state);
            printf("\n");
        }
        if (current_turn > n || is_player_won || game_state.steps.r[STEP] <= 0) is_game_over = 1;
        
        num_target_locations = sort_target_locations(target_locations_sorted, &game_state);
    }

    }

    // ### End of the main loop ###

    if (!game_state.steps.r[STEP])
        printf("No more steps. You lost :(\n");
    else if (is_player_won)
        printf("Congratulations!!! You found the exit\n");
    else if (current_turn > n)
        printf("You took too long. You lost :(\n");
    else
        printf("You lost :(\n");

    return 0;
}
