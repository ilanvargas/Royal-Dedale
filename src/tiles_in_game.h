#include "tile.h"

#define MAX_TILE_NAME_LENGTH 40

/** Implementation of the type of tile 
 */

struct tile_t
{
  char name[MAX_TILE_NAME_LENGTH];
  struct stash_t traversal_cost;
  struct stash_t opening_cost[MAX_DIRS];
};

//Basic tile

struct tile_t EMPTY_TILE = {
  .name = "empty",
  .traversal_cost = INFINITE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
  }
};

struct tile_t START_TILE  = {
  .name = "start",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
};

struct tile_t EXIT_TILE = {
  .name = "exit",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
};

//Game tile

struct tile_t CLOISTER_TILE = {
  .name = "cloister",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t N_TERRACE_TILE = {
  .name = "n terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t E_TERRACE_TILE = {
  .name = "e terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t W_TERRACE_TILE = {
  .name = "w terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t S_TERRACE_TILE = {
  .name = "s terrace",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t EW_CORRIDOR_TILE = {
  .name = "ew corridor",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t NS_CORRIDOR_TILE = {
  .name = "ns corridor",
  .traversal_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};

#define TILES_NUMBER 10
/*
struct tile_t* tiles_adress[] = {
  &EMPTY_TILE,
  &START_TILE,
  &EXIT_TILE,
  &CLOISTER_TILE
  &N_TERRACE_TILE
  &E_TERRACE_TILE
  &W_TERRACE_TILE
  &S_TERRACE_TILE
  &EW_CORRIDOR_TILE
  &NS_CORRIDOR_TILE
};*/
char* tiles_name[] = {
  "empty",
  "start",
  "exit",
  "cloister",
  "n terrace",
  "e terrace",
  "w terrace",
  "s terrace",
  "ew corridor",
  "ns corridor"
};
