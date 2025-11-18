#include "../src/tile.h"
#include "../src/tiles_in_game.h"
#include <stdio.h>

int test_tile_name(char* output, char* solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m output: %s\n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

int equal_stash(struct stash_t a, struct stash_t b)
{
  for (int i = 1; i <= MAX_RESOURCES; i++)
    if (a.r[i] != b.r[i]) return 0;
  return 1;
}
void print_stash(struct stash_t stash)
{
  for (int i = 0; i <= MAX_RESOURCES; i++)
    printf("");
}

int test_tile_traversal_or_opening_cost(struct stash_t output, struct stash_t solution)
{
  if (equal_stash(output, solution)) {
    printf("\e[1;32mPASSED\e[0m output: \n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: \t solution: \n", output, solution);
    return 0;
  }
}

int test_tile_generate(struct tile_t* output, struct tile_t* solution)
{

}

void tests_tile()
{
  printf("\n");
  printf("\e[1mTESTS ON tile.c\e[0m\n");
}
