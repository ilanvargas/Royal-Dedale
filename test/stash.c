#include <stdio.h>
#include <string.h>
#include "../src/stash.h"

//Test fonctions
int test_stasht_to_string(const char *output, char *solution)
{
  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m output: %s\n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

int test_stasht_formated(struct stash_t *output, struct stash_t *solution)
{
  //assuming that stash_to_string passed the tests, we use it only for aesthetics purposes
  int passed = 1;
  for (int i = 0; i < NUM_RESOURCES+1; i++) 
    if (output->r[i] != solution->r[i]) {
      passed = 0;
      break;
    }
  char o[MAX_STASH_STRING_LENGTH];
  stash_to_string(output, o);
  if (passed) {
    printf("\e[1;32mPASSED\e[0m output: %s\n", o);
    return 1;
  } else {
    char s[MAX_STASH_STRING_LENGTH];
    stash_to_string(solution, s);
    printf("\e[1;31mFAILED\e[0m output: %s\t solution: %s\n", o, s);
    return 0;
  }
}

//Tests
void tests_stash()
{
  printf("\n");
  printf("\e[1mTESTS ON stash.c\e[0m\n");

  printf("Tests on stash_to_string\n");
  int nb_tests = 4;
  struct stash_t input[] = {(struct stash_t){{1,0,4,3,5}},
                            (struct stash_t){{0,10,300,400,9999}},
                            EMPTY_STASH,
                            INFINITE_STEP_STASH
                            };
  for (int i = 0; i < nb_tests; i++) {
    char buffer[MAX_STASH_STRING_LENGTH];
    stash_to_string(&input[i], buffer);
    test_stasht_to_string(buffer, "yo");
  }

  printf("Tests on stash_add\n");
  int nb_tests1 = 2;
  struct stash_t inputA[] = {(struct stash_t){{1,2,3,4,5}},
                             (struct stash_t){{20,99,0,7,51}},
                            };
  struct stash_t inputB[] = {(struct stash_t){{1,2,3,4,5}},
                             (struct stash_t){{0,3,0,345,51}},
                            };
  struct stash_t solution1[] = {(struct stash_t){{2,4,6,8,10}},
                                (struct stash_t){{20,102,0,352,102}},
                                };
  for (int i = 0; i < nb_tests1; i++) {
    struct stash_t output = stash_add(&inputA[i], &inputB[i]);
    test_stasht_formated(&output, &solution1[i]);
  }
}
