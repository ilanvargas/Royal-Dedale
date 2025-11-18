/** Implementation of the type of tiles 
 */

struct tile_t
{
    char *name;
    struct stash_t traversal_cost;
    struct stash_t opening_cost[MAX_DIRS];
};

//Basic tiles
struct tiles_t EMPTY_TILE = {
  .name = "",
  .travel_cost = INFINITE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
  }
};

struct tiles_t START_TILE  = {
  .name = "start",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
  }
}

struct tiles_t EXIT_TILE = {
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

struct tile_t CLOISTER_TILE = {
  .name = "cloister",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH
    }
};

struct tile_t N_TERRACE_TILE = {
  .name = "n terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t E_TERRACE_TILE = {
  .name = "e terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t W_TERRACE_TILE = {
  .name = "w terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t S_TERRACE_TILE = {
  .name = "s terrace",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};


struct tile_t EW_CORRIDOR_TILE = {
  .name = "ew corridos",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    INFINITE_STEP_STASH,
    ONE_STEP_STASH,
    ONE_STEP_STASH,
    INFINITE_STEP_STASH
    }
};

struct tile_t NS_CORRIDOR_TILE = {
  .name = "ns corridor",
  .travel_cost = ONE_STEP_STASH,
  .opening_cost = {
    ONE_STEP_STASH,
    INFINITE_STEP_STASH,
    INFINITE_STEP_STASH,
    ONE_STEP_STASH
    }
};
