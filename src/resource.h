#ifndef __DEDALE_RESOURCE_H__
#define __DEDALE_RESOURCE_H__

/** The number of resources in the game.
 *
 * Note that this number counts the resources different from
 * NOTHING. For example, if NUM_RESOURCES = 4, the game uses resources
 * from STEP to GOLD included. Obviously, this number must be less
 * than MAX_RESOURCES.
 */
#ifndef NUM_RESOURCES
#define NUM_RESOURCES 4
#endif  // NUM_RESOURCES

/** Enumeration of all possible resources in the game. */
enum resource_t {
  NOTHING = 0,
  STEP = 1,
  KEY = 2,
  GEM = 3,
  GOLD = 4,
  SILK = 5,
  FUR = 6,
  INCENSE = 7,
  POTION = 8,
  OIL = 9,
  CRYSTAL = 10,
  MAX_RESOURCES = 10,
};

/** Returns the string representation of the resource `r`. */
const char* resource_to_string(enum resource_t r);

/** Returns the short string representation of the resource `r`, usually
 * only one character long. */
const char* resource_to_short_string(enum resource_t r);

#endif  // __DEDALE_RESOURCE_H__
