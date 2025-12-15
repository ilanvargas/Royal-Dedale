#include <stdio.h>
#include <string.h>
#include "dir.h"

//Test fonctions
int test_dirt_to_string(enum dir_t input, const char *output, char *solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: %d\t output: %s\n", input, output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %d\t output: %s\t solution: %s\n", input, output, solution);
    return 0;
  }
}

int test_dirt_to_string_formated(enum dir_t input, const char *output, char *solution)
{
  //we assume that the tests of dir_to_str passed, we use it only for aesthetics purposes
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: %d\t output: %s\n", input, output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %d\t output: %s\t solution: %s\n", input, output, solution);
    return 0;
  }
}

int test_dirt_to_t_formated(enum dir_t input, enum dir_t output, enum dir_t solution)
{
  //we assume that the tests of dir_to_str passed, we use it only for aesthetics purposes
  if (output == solution) {
    printf("\e[1;32mPASSED\e[0m input: %s\t output: %s\n", dir_to_string(input), dir_to_string(output));
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %s\t output: %s\t solution: %s\n", dir_to_string(input), dir_to_string(output), dir_to_string(solution));
    return 0;
  }
}

//Tests
void tests_dir()
{
  printf("\e[1mTESTS ON dir.c\e[0m\n");

  printf("Tests on dir_to_string\n");
  int nb_tests = 5;
  enum dir_t input[] = {NORTH, EAST, SOUTH, WEST, INVALID_DIR};
  char *solution[] = {"NORTH", "EAST", "SOUTH", "WEST", ""};
  for (int i = 0; i < nb_tests; i++) {
    test_dirt_to_string(input[i], dir_to_string(input[i]), solution[i]);
  }

  printf("Tests on dir_to_short_string\n");
  char *solution1[] = {"N", "E", "S", "W", ""};
  for (int i = 0; i < nb_tests; i++) {
    test_dirt_to_string_formated(input[i], dir_to_short_string(input[i]), solution1[i]);
  }

  printf("Tests on dir_opposite\n");
  enum dir_t solution2[] = {SOUTH, WEST, NORTH, EAST, INVALID_DIR};
  for (int i = 0; i < nb_tests; i++) {
    test_dirt_to_t_formated(input[i], dir_opposite(input[i]), solution2[i]);
  }
}

