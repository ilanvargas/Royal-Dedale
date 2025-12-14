#include <stdlib.h>
#include "target.h"

unsigned int distance(struct location_t a, struct location_t b)
{
    return abs(b.x - a.x) + abs(b.y - a.y);
}

void select_target_positions(struct game_state_t* game_state, struct location_t target_positions[3])
{

    int c = 0;
    while (c < 3)
    {
        unsigned int rand_x = rand()%BOARD_WIDTH;
        unsigned int rand_y = rand()%BOARD_HEIGHT;
        if ((rand_x != 0 || rand_y != 0) && (rand_x != BOARD_WIDTH || rand_y != BOARD_HEIGHT))
        {
            target_positions[c] = location(rand_x, rand_y);
            c++;
        }
    }
}

void sort_target_positions(struct location_t current_location, struct location_t target_positions[3])
{
    unsigned int dist0 = distance(current_location, target_positions[0]);
    unsigned int dist1 = distance(current_location, target_positions[1]);
    unsigned int dist2 = distance(current_location, target_positions[2]);
    if (dist0 > dist1)
    {
        struct location_t temp = target_positions[0];
        target_positions[0] = target_positions[1];
        target_positions[1] = temp;
    }
    if (dist1 > dist2)
    {
        struct location_t temp = target_positions[1];
        target_positions[1] = target_positions[2];
        target_positions[2] = temp;
    }
    if (dist0 > dist1)
    {
        struct location_t temp = target_positions[0];
        target_positions[0] = target_positions[1];
        target_positions[1] = temp;
    }
}

void init_game_state(unsigned int game_seed, struct location_t *target_positions, struct game_state_t *game_state)
{
  game_state->steps.r[STEP] = 4 * BOARD_SIZE / 3;
  
  for (int i = 0; i < BOARD_WIDTH; i++) {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
      game_state->board[i][j].tile = tile_generate_empty();
    }
  }
  game_state->board[0][0].tile = tile_generate_start();
  game_state->board[BOARD_WIDTH-1][BOARD_HEIGHT-1].tile = tile_generate_exit();
  select_target_positions(game_state, target_positions);
  game_state->current_location = location(0, 0);
  sort_target_positions(game_state->current_location, target_positions);

  srand(game_seed);
}

struct location_t dir_to_location(enum dir_t d, struct location_t current_location)
{
    switch(d){
        case 0:
            return location(current_location.x, current_location.y + 1);
        case 1:
            return location(current_location.x - 1, current_location.y);
        case 2:
            return location(current_location.x, current_location.y - 1);
        case 3:
            return location(current_location.x + 1, current_location.y);
        default:
            return location(BOARD_WIDTH,BOARD_HEIGHT);
    }
}

struct location_t next_target_position(unsigned int num_visited_positions, struct location_t *target_positions)
{
    switch (num_visited_positions){ 
        case 3:
            return location(BOARD_WIDTH-1,BOARD_HEIGHT-1);
        case 2:
            return target_positions[2];
        case 1:
            return target_positions[1];
        case 0:
            return target_positions[0];
        default:
            return location(BOARD_WIDTH,BOARD_HEIGHT);
    }
}

int target_position_reached(struct game_state_t *game_state, unsigned int num_visited_positions, struct location_t *target_positions)
{
    if (location_equal(game_state->current_location, target_positions[num_visited_positions]) || exit_reached(game_state))
    {
        switch(num_visited_positions){
            case 0:
                struct stash_t res = game_state->steps;
                game_state->steps = stash_add(&res,&BBFINAL_RESOURCE);
            case 1:
                struct stash_t res = game_state->steps;
                game_state->steps = stash_add(&res,&BFINAL_RESOURCE);
            case 2:
                struct stash_t res = game_state->steps;
                game_state->steps = stash_add(&res,&FINAL_RESOURCE);
            case 3:
                if (exit_reached(game_state)) return 1;
                return 0;
            default:
                break;

        }
        return 1;
    }
    return 0;
}


void find_path(struct game_state_t* game_state, struct location_t first_position, struct location_t target_postion, struct location_t *return_empty_location, int is_visited_position[BOARD_WIDTH][BOARD_HEIGHT], struct location_t path[BOARD_SIZE], int *path_length)
{
    is_visited_position[first_position.x][first_position.y] = 1;

    struct location_t last_empty_location;
    for (int d = 0; d < MAX_DIRS; d++)
    {
        struct location_t current_path[BOARD_SIZE];
        int current_path_len = 0;
        struct location_t next_position = dir_to_location(d, first_position);
        if (location_is_valid(next_position) && !is_visited_position[next_position.x][next_position.y])
        {

            if ((tile_is_empty(location_to_tile(next_position, game_state).tile)))
            {
                last_empty_location = next_position;
                if (distance(last_empty_location, target_postion) < distance(*return_empty_location, target_postion))
                {
                    *return_empty_location = last_empty_location;
                }
            }
            else if (tile_can_open_bis(location_to_tile(next_position, game_state), dir_opposite(d)))
            {
                path[*path_length] = next_position;
                *path_length++;
                find_path(game_state, next_position, target_postion, return_empty_location, is_visited_position, path, path_length);
            }
        }
    }
}

