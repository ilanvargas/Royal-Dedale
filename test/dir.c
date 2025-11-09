#include <stdio.h>
#include "../src/dir.h"
#include "test.h"

void tests_dir()
{
  printf("TESTS ON DIR.C\n");

  printf("Tests on dir_to_string\n");
  int nb_tests = 5;
  enum dir_t input[] = {NORTH, EAST, SOUTH, WEST, INVALID_DIR};
  char *solution[] = {"NORTH", "EAST", "SOUTH", "WEST", ""};
  for (int i = 0; i < nb_tests; i++) {
    test_X_to_str(&input[i], dir_to_string(input[i]), solution[i]);
  }

  printf("Tests on dir_to_short_string\n");
  char *solution1[] = {"N", "E", "S", "W", ""};
  for (int i = 0; i < nb_tests; i++) {
    test_X_to_str(&input[i], dir_to_short_string(input[i]), solution1[i]);
  }

  printf("Tests on dir_opposite\n");
  enum dir_t solution2[] = {SOUTH, WEST, NORTH, EAST, INVALID_DIR};
  for (int i = 0; i < nb_tests; i++) {
    const enum dir_t o = dir_opposite(input[i]);
    test_X_to_X(&input[i], &o, &solution2[i]);
  }

}

