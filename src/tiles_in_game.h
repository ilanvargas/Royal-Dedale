/** Implementation of the type of tiles 
 */

struct tile_t
{
    char *name;
    struct stash_t traversal_cost;
    struct stash_t opening_cost[MAX_DIRS];
};

//Basic tiles
struct tiles_t EMPTY = {
  .name = "",
  .travel_cost = INFINITE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
  }
}

struct tiles_t START = {
  .name = "start",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
}

struct tiles_t EXIT = {
  .name = "exit",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
}

//Game tiles

struct tile_t CLOISTER = {
  .name = "cloister",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t N_TERRACE = {
  .name = "n terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t E_TERRACE = {
  .name = "e terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t W_TERRACE = {
  .name = "w terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t S_TERRACE = {
  .name = "s terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};


struct tile_t E-W_CORRIDOR = {
  .name = "e-w corridos",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t N-S_CORRIDOR = {
  .name = "n-s corridor",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};
