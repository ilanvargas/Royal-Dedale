#ifndef __DEDALE_DIR_H__
#define __DEDALE_DIR_H__

/** Enumeration of the four cardinal directions. */
enum dir_t {
  NORTH = 0,
  EAST = 1,
  SOUTH = 2,
  WEST = 3,
  MAX_DIRS = 4,
  INVALID_DIR = 5,
};

/** Returns the string representation of the direction `d`. */
const char* dir_to_string(enum dir_t d);

/** Returns the short string representation of the direction `d`, usually
 * only one character long. */
const char* dir_to_short_string(enum dir_t d);

/** Returns the opposite direction of the direction `d`. */
enum dir_t dir_opposite(enum dir_t d);

#endif  // __DEDALE_DIR_H__