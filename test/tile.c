#include <stdio.h>
#include <string.h>
#include "tile.h"


void print_stash(const struct stash_t* stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s: %d ,", resource_to_short_string(i), stash->r[i]);
  printf("\n");
}

int equal_stash(const struct stash_t* a, const struct stash_t* b)
{
  for (int i = 1; i <= MAX_RESOURCES; i++)
    if (a->r[i] != b->r[i]) return 0;
  return 1;
}

void print_tile(const struct tile_t* tile)
{
  printf("tile: %s, ", tile_name(tile));
  char ch[MAX_STASH_STRING_LENGTH];
  struct stash_t tr = tile_traversal_cost(tile);
  stash_to_string(&tr, ch);
  printf("traversal cost: %s, ", ch);
  printf("opening cost in: ");
  for (int i = 0; i < MAX_DIRS; i++)
  {
    printf("%s: ", dir_to_short_string(i));
    char sh[MAX_STASH_STRING_LENGTH];
    struct stash_t op = tile_opening_cost(tile, i);
    stash_to_string(&op, sh);
    printf("%s", sh);
    printf("  ");
  }
  printf("\n");
}

int test_tile_name(const struct tile_t* input, const char* output, const char* solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf("\t output: %s\n", output);
    return 1;
  } 
  else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf("\t output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

int test_tile_traversal_cost(const struct stash_t* input, struct stash_t output, struct stash_t solution)
{
  if (equal_stash(&output, &solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_stash(input);
    printf("\t output: ");
    print_stash(&output);
    printf("\n");
    return 1;
  } 
  else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_stash(input);
    printf("\t output: ");
    print_stash(&output);
    printf("\t solution: ");
    print_stash(&solution);
    printf("\n");
    return 0;
  }
}

int test_tile_opening_cost(const struct tile_t* input, enum dir_t d, struct stash_t output, struct stash_t solution)
{
  if (!equal_stash(&output, &solution)) {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf(", %s", dir_to_short_string(d));
    printf("\t output: ");
    print_stash(&output);
    printf("\t solution: ");
    print_stash(&solution);
    printf("\n");
    return 0;
  }
  else {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf(", %s", dir_to_short_string(d));
    printf("\t output: ");
    print_stash(&output);
    printf("\n");
    return 1;
  }
}
/*
int test_tile_generate(struct tile_t* output, struct tile_t* solution)
{

}*/

void tests_tile()
{
  printf("HAHAHA");
}
