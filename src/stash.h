#ifndef __DEDALE_STASH_H__
#define __DEDALE_STASH_H__

#include "resource.h"

#include <limits.h>

/** Structure representing a stash (i.e a set) of resources. */
struct stash_t {
  unsigned int r[NUM_RESOURCES + 1];
};

/** The maximal length of a string representation of a resource. */
#define MAX_STASH_STRING_LENGTH 128

/** An empty stash, containing no resources. */
#define EMPTY_STASH  \
  (struct stash_t) { \
    .r = {0}         \
  }

/** A stash representing exactly one step. */
#define ONE_STEP_STASH \
  (struct stash_t) {   \
    .r = {[STEP] = 1}  \
  }

/** A stash representing an infinite amount of resources. Typically, this
 * kind of stash cannot be paid during the game. */
#define INFINITE_STEP_STASH    \
  (struct stash_t) {           \
    .r = { [STEP] = UINT_MAX } \
  }

/** Converts a stash to a string representation into `buffer`.
 * `buffer` must be allocated and able to contain
 * MAX_STASH_STRING_LENGTH characters. The function cannot write more
 * than MAX_STASH_STRING_LENGTH into `buffer`, the '0' terminator included. */
void stash_to_string(const struct stash_t* stash, char* buffer);

/** Adds two stashes and returns the result. */
struct stash_t stash_add(const struct stash_t* a, const struct stash_t* b);

/** Subtracts stash `b` from stash `a` and returns the result. If `b`
 * contains more resources than `a`, the result will contain zero
 * resources for those types. */
struct stash_t stash_sub(const struct stash_t* a, const struct stash_t* b);

/** Checks if stash `b` is contained within stash `a`. Can be used to check
 * if the player has enough resources to pay a cost. */
int stash_contains(const struct stash_t* a, const struct stash_t* b);

#endif  // __DEDALE_STASH_H__
