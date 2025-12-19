#include "equipement.h"
#include <stdlib.h>
#include <stdio.h>

void init_equipement(unsigned int equipement_seed)
{
    srand(equipement_seed);
}

const char* equipement_to_string(enum equipement_t equipement)
{
    switch (equipement)
    {
        case 0:
            return "SHOVEL";
        case 1:
            return "WALLET";
        case 2:
            return "SNEAKERS";
        case 3:
            return "CHAPELS";
        default:
            return "";
    }
}

void can_gain_equipement(struct game_state_t* game_state)
{
    float probability = 1 / BOARD_SIZE;
    float random = (float)rand() / RAND_MAX;
    if (random < probability)
    {
        int gained_equipement = 0;
        int i = 0;
        while (i < NUM_EQUIPEMENTS && !gained_equipement)
        {
            int r = rand() % NUM_EQUIPEMENTS;
            if (!game_state->has_equipements[r])
            {
                game_state->has_equipements[r] = 1;
                gained_equipement = 1;
                printf("Congratulations ! You have gained the equipement : %s\n", equipement_to_string(r));
            }
            else
            {
                if (r < NUM_EQUIPEMENTS - 1)
                {
                    r = r + 1;
                    i++;
                }
                else
                {
                    r = 0;
                    i++;
                }
            }
        }
    }
}

void on_tile_open(struct game_state_t* game_state)
{
    if (game_state->has_equipements[SHOVEL])
    {
        float probability = 1 / BOARD_SIZE;
        float random = (float) rand() / RAND_MAX;
        if (random < probability)
        {
            int rand_resource = 1 + ( rand() / (NUM_RESOURCES-1) );
            game_state->steps.r[rand_resource] += 1;
            printf("You have won a %s\n", resource_to_string(rand_resource));
        }
    }
    if (game_state->has_equipements[CHAPELS])
    {
        game_state->steps.r[STEP] += 1;
        printf("Chapels gave you a step ;)\n");
    }
}

int player_gained_resources(const struct stash_t gained_resources)
{
    for (int i = 1; i < NUM_RESOURCES+1; i++)
    {
        if (gained_resources.r[i]) return 1;
    }
    return 0;
}

void on_resource_gain(struct game_state_t* game_state, const struct stash_t gained_resources)
{
    if (player_gained_resources(gained_resources))
    {
        if (gained_resources.r[GOLD] && game_state->has_equipements[WALLET])
        {
            game_state->steps.r[GOLD] += 1;
            printf("You have won another GOLD !!\n");
        }

        if (game_state->has_equipements[CHAPELS])
        {
            game_state->steps.r[STEP] += 1;
            printf("Chapels gave you a step ;)\n");
        }
    }
}

void on_move(struct game_state_t *game_state)
{
    if (game_state->has_equipements[SNEAKERS])
    {
        float probability = 1 / 3;
        float random = (float) rand() / RAND_MAX;

        if (random < probability)
        {
            game_state->steps.r[STEP] += 1;
            printf("Your sneakers gave you a refund step for your hard training ! stay fit ;)\n");
        }
    }
    if (game_state->has_equipements[CHAPELS])
    {
        game_state->steps.r[STEP] += 1;
        printf("Chapels gave you a step ;)\n");
    }
}