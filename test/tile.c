#include "../src/tile.h"
#include "../src/tiles_in_game.h"
#include <stdio.h>

void print_stash(struct stash_t* stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s: %d ,", resource_to_short_string(i), stash->r[i]);
  printf("\n");
}

int equal_stash(const struct stash_t a, const struct stash_t b)
{
  for (int i = 1; i <= MAX_RESOURCES; i++)
    if (a.r[i] != b.r[i]) return 0;
  return 1;
}

void print_tile(struct tile_t* tile)
{
  printf("%s, ", tile->name);
  printf("traversal cost: ,");
  print_stash(&tile->traversal_cost);
  printf("opening cost in: ");
  for (int i = 0; i < MAX_DIRS; i++)
  {
    printf("%s: ", dir_to_short_string);
    print_stash(&tile->opening_cost[i]);
    printf("  ");
  }
  printf("\n");
}

int test_tile_name(const struct tile_t* input, char* output, char* solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_stash(&input);
    printf("output: %s\n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_stash(&input);
    printf("output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

int test_tile_traversal_cost(const struct stash_t input, struct stash_t output, struct stash_t solution)
{
  if (equal_stash(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_stash(&input);
    printf("\t output: \n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: \t solution: \n", output, solution);
    return 0;
  }
}

int test_tile_opening_cost(const struct stash_t input, enum dir_t d, struct stash_t output, struct stash_t solution)
{
  for (int i = 0; i < MAX_DIRS; i++)
  { 
    if (equal_stash(output, solution) == 0) {
      printf("\e[1;31mFAILED\e[0m input: ");
      print_stash(&input);
      printf("\t output: ");
      print_stash(&output);
      printf("\t solution: ");
      print_stash(&solution);
      printf("\n");
      return 0;
    }
  }
  printf("\e[1;32mPASSED\e[0m input: ");
  print_stash(&input);
  printf("\t output: \n", output);
  return 1;
}

int test_tile_generate(struct tile_t* output, struct tile_t* solution)
{

}

void tests_tile()
{
  printf("\n");
  printf("\e[1mTESTS ON tile.c\e[0m\n");

  printf("Tests on tile_name\n");
  int nb_tests = 5;
  const struct tile_t* input[] = { &EMPTY_TILE, &START_TILE, &CLOISTER_TILE, &E_TERRACE_TILE, &EW_CORRIDOR_TILE };
  char* solution[] = {"empty", "start", "cloister", "e terrace", "ew corridor"};
  for (int i = 0; i < nb_tests; i++)
  {
    char* output = tile_name(input[i]);
    test_tile_name(input[i], output, solution[i]);
  }

}
