#include "dir.h"

const char* dir_to_string(enum dir_t d)
{
  switch (d) {
    case NORTH:
      return "NORTH";
    case EAST:
      return "EAST";
    case SOUTH:
      return "SOUTH";
    case WEST:
      return "WEST";
    default:
      return "";
  }
}

const char* dir_to_short_string(enum dir_t d)
{
  switch (d) {
    case NORTH:
      return "N";
    case EAST:
      return "E";
    case SOUTH:
      return "S";
    case WEST:
      return "W";
    default:
      return "";
  }
}

enum dir_t dir_opposite(enum dir_t d)
{
  switch (d) {
    case NORTH:
      return SOUTH;
    case EAST:
      return WEST;
    case SOUTH:
      return NORTH;
    case WEST:
      return EAST;
    default:
      return INVALID_DIR;
  }
}
