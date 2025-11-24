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
  printf("%s\n", tile_name(tile));
  char ch[MAX_STASH_STRING_LENGTH];
  struct stash_t tr = tile_traversal_cost(tile);
  stash_to_string(&tr, ch);
  printf("traversal cost: %s, \n", ch);
  printf("opening cost in:\n");
  for (int i = 0; i < MAX_DIRS; i++)
  {
    printf("%s: ", dir_to_short_string(i));
    char sh[MAX_STASH_STRING_LENGTH];
    struct stash_t op = tile_opening_cost(tile, i);
    stash_to_string(&op, sh);
    printf("%s\n", sh);
  }
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
  printf("\n");
  printf("\e[1mTESTS ON tile.c\e[0m\n");

  printf("Tests on tile_name\n");
  int nb_tests = 5;
  const struct tile_t* input[] = { &EMPTY_TILE, &START_TILE, &CLOISTER_TILE, &E_TERRACE_TILE, &EW_CORRIDOR_TILE };
  const char* solution[] = {"empty", "start", "cloister", "e terrace", "ew corridor"};
  for (int i = 0; i < nb_tests; i++)
  {
    const char* output = tile_name(input[i]);
    test_tile_name(input[i], output, solution[i]);
  }
  
}
