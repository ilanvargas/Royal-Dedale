#include "dir.h"
#include "stash.h"

struct tile_t
{
    char *name;
    struct stash_t traversal_cost;
    struct stash_t opening_cost_north;
    struct stash_t opening_cost_south;
    struct stash_t opening_cost_east;
    struct stash_t opening_cost_west;

};

void init_tiles(unsigned int tile_seed);

const char* tile_name(const struct tile_t* tile)
{
    return tile->name;
}

struct stash_t tile_traversal_cost(const struct tile_t* tile)
{
    return tile->traversal_cost;
}

struct stash_t tile_opening_cost(const struct tile_t* tile, enum dir_t d)
{
    if (dir_to_short_string == "N") return tile->opening_cost_north;
    else if (dir_to_short_string == "S") return tile->opening_cost_south;
    else if (dir_to_short_string == "E") return tile->opening_cost_east;
    else if (dir_to_short_string == "W") return tile->opening_cost_west;
    else return INFINITE_STEP_STASH;
}


struct tile_t* tile_generate_empty()
{
  return {.name = "empty",
          .traversal_cost = INFINITE_STEP_STASH,
          .opening_cost = {INFINITE_STEP_STASH}
          };
}
 

struct tile_t* tile_generate_start();
{
  return {.name = "start",
          .traversal_cost = ONE_STEP_STASH,
          .opening_cost = {ONE_STEP_STASH}
          };
}

struct tile_t* tile_generate_exit();
{
  return {.name = "exit",
          .traversal_cost = ONE_STEP_STASH,
          .opening_cost = {ONE_STEP_STASH}
          };
}

struct tile_t* tile_generate_by_name(const char* name);

unsigned int tile_draft(enum dir_t d, struct tile_t** results);

int tile_is_empty(const struct tile_t* tile)
{
  char* str_empty = "empty";
  char *p = tile->name;
  while (*p && *str_empty) {
    if (*p++ != *str_empty++) return 0; 
  }
  if (*p || *str_empty) return 0;
  return 1;
}

int tile_can_open(const struct tile_t* tile, enum dir_t d)
{
  if (tile->opening_cost[d].r[STEP] == UINT_MAX) return 0;
  return 1;
}
