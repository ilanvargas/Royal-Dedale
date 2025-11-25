#include <stdio.h>
#include <string.h>
#include <string.h>
#include "tile.h"

// EXAM ?
void print_stash(const struct stash_t* stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s:%d ", resource_to_short_string(i), (unsigned int)stash->r[i]);
  printf("\n");
}

int equal_stash(const struct stash_t* a, const struct stash_t* b)
{
  for (int i = 1; i <= NUM_RESOURCES; i++)
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

int is_tile(struct tile_t* a, struct tile_t* b)
{
  if (!strcmp(tile_name(a), tile_name(b))) return 1;
  else return 0;
}

int test_tile_name(const struct tile_t* input, const char* output, const char* solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf("output: %s\n", output);
    return 1;
  } 
  else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf("output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

int test_tile_traversal_cost(const struct tile_t* input, struct stash_t output, struct stash_t solution)
{
  if (equal_stash(&output, &solution)) {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf("output: ");
    print_stash(&output);
    return 1;
  } 
  else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf("output: ");
    print_stash(&output);
    printf("solution: ");
    print_stash(&solution);
    return 0;
  }
}

int test_tile_opening_cost(const struct tile_t* input, enum dir_t d, struct stash_t output, struct stash_t solution)
{
  if (!equal_stash(&output, &solution)) {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf(", direction %s\n", dir_to_short_string(d));
    printf("output: ");
    print_stash(&output);
    printf("solution: ");
    print_stash(&solution);
    return 0;
  }
  else {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf(", direction %s\n", dir_to_short_string(d));
    printf("output: ");
    print_stash(&output);
    return 1;
  }
}

int test_tile_generate(struct tile_t* output, struct tile_t* solution)
{
  if (is_tile(output, solution))
  {
    printf("\e[1;32mPASSED\e[0m output: ");
    print_tile(output);
    return 1;
  }
  else {
    printf("\e[1;31mFAILED\e[0m output: ");
    print_tile(output);
    printf("solution: ");
    print_tile(solution);
    return 0;
  }
}

int test_tile_generate_by_name(const char* input, struct tile_t* output, struct tile_t* solution)
{
  if (is_tile(output, solution))
  {
    printf("\e[1;32mPASSED\e[0m input: %s\noutput: ", input);
    print_tile(output);
    return 1;
  }
  else {
    printf("\e[1;31mFAILED\e[0m input: %s\noutput: ", input);
    print_tile(output);
    printf("solution: ");
    print_tile(solution);
    return 0;
  }
}

int test_tile_draft(enum dir_t input, unsigned int output, unsigned int solution)
{
  if (output == solution) {
    printf("\e[1;32mPASSED\e[0m input: %s\t output: %d\n", dir_to_short_string(input), output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %s\t output: %d\t solution: %d\n", dir_to_short_string(input), output, solution);
    return 0;
  }
}

int test_tile_can_open(const struct tile_t* input, enum dir_t d, int output, int solution)
{
  if (output == solution)
  {
    printf("\e[1;32mPASSED\e[0m input: ");
    print_tile(input);
    printf("direction: %s\n", dir_to_short_string(d));
    printf("output: %d\n", output);
    return 1;
  }
  else {
    printf("\e[1;31mFAILED\e[0m input: ");
    print_tile(input);
    printf("direction: %s\n", dir_to_short_string(d));
    printf("output: %d\t solution: %d\n", output, solution);
    return 0;
  }
}

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
  
  printf("\nTests on tile_traversal_cost\n");
  int nb_tests1 = 3;
  const struct tile_t* input1[] = { &EMPTY_TILE, &START_TILE, &E_TERRACE_TILE };
  struct stash_t solution1[] = { INFINITE_STEP_STASH, ONE_STEP_STASH, ONE_STEP_STASH };
  for (int i = 0; i < nb_tests1; i++)
  {
    struct stash_t output1 = tile_traversal_cost(input1[i]);
    test_tile_traversal_cost(input1[i], output1, solution1[i]);
  }

  printf("\nTests on tile_opening_cost\n");
  int nb_tests2 = 5;
  const struct tile_t* input2[] = { &EMPTY_TILE, &START_TILE, &E_TERRACE_TILE, &E_TERRACE_TILE, &NS_CORRIDOR_TILE };
  enum dir_t d2[] = {NORTH, EAST, EAST, WEST, SOUTH};
  struct stash_t solution2[] = { INFINITE_STEP_STASH, ONE_STEP_STASH, ONE_STEP_STASH, INFINITE_STEP_STASH, ONE_STEP_STASH };
  for (int i = 0; i < nb_tests2; i++)
  {
    struct stash_t output2 = tile_opening_cost(input2[i],d2[i]);
    test_tile_opening_cost(input2[i], d2[i], output2, solution2[i]);
  }

  printf("\nTest on tile_generate_empty\n");
  struct tile_t* solutiona = &EMPTY_TILE;
  struct tile_t* outputa = tile_generate_empty();
  test_tile_generate(outputa, solutiona);
  printf("Test on tile_generate_start\n");
  struct tile_t* solutionb = &START_TILE;
  struct tile_t* outputb = tile_generate_start();
  test_tile_generate(outputb, solutionb);
  printf("Test on tile_generate_exit\n");
  struct tile_t* solutionc = &EXIT_TILE;
  struct tile_t* outputc = tile_generate_exit();
  test_tile_generate(outputc, solutionc);

  printf("\nTests on tile_generate_by_name\n");
  int nb_tests3 = 4;
  const char* input3[] = { "empty", "start", "ew corridor", "s terrace" };
  struct tile_t* solution3[] =  { &EMPTY_TILE, &START_TILE, &EW_CORRIDOR_TILE, &S_TERRACE_TILE };
  for (int i = 0; i < nb_tests3; i++)
  {
    struct tile_t* output3 = tile_generate_by_name(input3[i]);
    test_tile_generate_by_name(input3[i], output3, solution3[i]);
  }

  /*printf("\nTests on tile_draft\n");
  struct tile_t results1[NUM_TILES_PER_TURN];
  int */

  printf("\nTests on tile_can_open\n");
  int nb_tests5 = 6;
  const struct tile_t* input5[] = { &EMPTY_TILE, &START_TILE, &EW_CORRIDOR_TILE, &EW_CORRIDOR_TILE, &N_TERRACE_TILE, &N_TERRACE_TILE  };
  enum dir_t d5[] = {SOUTH, WEST, EAST, NORTH, NORTH, SOUTH};
  int solution5[] = {0, 1, 1, 0, 1, 0};
  for (int i = 0; i < nb_tests5; i++)
  {
    int output5 = tile_can_open(input5[i], d5[i]);
    test_tile_can_open(input5[i], d5[i], output5, solution5[i]);
  } 
}
