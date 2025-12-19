#ifndef __DEDALE_EQUIPEMENT_H__
#define __DEDALE_EQUIPEMENT_H__

#include "target.h"

/** enumeration of the equipements in game */
enum equipement_t {
    SHOVEL = 0,
    WALLET = 1,
    SNEAKERS = 2,
    CHAPELS = 3,
    MAX_EQUIPEMENTS = 4,

};

/** returns the string representation for an equipement */
const char* equipement_to_string(enum equipement_t equipement);

/** gives the player a chance to win a random equipement with a probability of 1 / BOARD_SIZE
 * updates the has_equipement array in the game_state if the player gained an equipement
 */
void can_gain_equipement(struct game_state_t* game_state);

/** checking if the player has the equipements that can be applied after opening a tile and applying them */
void on_tile_open(struct game_state_t* game_state);

/** verifies if the gained resources array isn't empty */
int player_gained_resources(const struct stash_t gained_resources);

/** checking if the player has the equipements that can be applied after gaining resources and applying them */
void on_resource_gain(struct game_state_t* game_state, const struct stash_t gained_resources);

/** checking if the player has the equipements that can be applied after moving and applying them */
void on_move(struct game_state_t *game_state, const struct stash_t gained_resources);

#endif  // __DEDALE_EQUIPEMENT_H__