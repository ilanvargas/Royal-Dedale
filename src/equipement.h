#ifndef __DEDALE_EQUIPEMENT_H__
#define __DEDALE_EQUIPEMENT_H__

#include "target.h"

enum equipement_t {
    SHOVEL = 0,
    WALLET = 1,
    SNEAKERS = 2,
    CHAPELS = 3,
    MAX_EQUIPEMENTS = 4,

};

const char* equipement_to_string(enum equipement_t equipement);

void can_gain_equipement(struct game_state_t* game_state);

void on_tile_open(struct game_state_t* game_state);

int player_gained_resources(const struct stash_t gained_resources);

void on_resource_gain(struct game_state_t* game_state, const struct stash_t gained_resources);

void on_move(struct game_state_t *game_state, const struct stash_t gained_resources);

#endif  // __DEDALE_EQUIPEMENT_H__