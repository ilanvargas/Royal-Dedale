#include "stach.h"

void stash_to_string(const struct stash_t* stash, char* buffer)
{
  char chaine[MAX_STASH_STRING_LENGTH];
  int i = 0;
  int j = 0;
  while (i < NUM_RESSOURCES+1 && j < MAX_STASH_STRING_LENGTH) {
    chaine[j++] = (char)stash->r[i++];
    chaine[j++] = " "
  }
  chaine[j] = '\0';

  buffer = chaine;
}

struct stash_t stash_add(const struct stash_t* a, const struct stash_t* b)
{
  struct stash_t c;
  for (int i = 0; i < NUM_RESSOURCES+1; i++) {
    c.r[i] = a->r[i] + b->r[i]
  }
  return c;
}

struct stash_t stash_sub(const struct stash_t* a, const struct stash_t* b)
{
  struct stash_t c;
  for (int i = 0; i < NUM_RESSOURCES+1; i++) {
    c.r[i] = (a->r[i] - b->r[i] > 0) ? a->r[i] - b->r[i] : 0;
  }
  return c;
}

struct stash_t stash_sub(const struct stash_t* a, const struct stash_t* b)
{
  struct stash_t c;
  for (int i = 0; i < NUM_RESSOURCES+1; i++) {
    if (a->r[i] - b->r[i] < 0) return 0;
  }
  return 1;
}
