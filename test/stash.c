#include <stdio.h>
#include <string.h>
#include "../src/stash.h"

//Test fonctions
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

int test_stasht_to_int_formated(struct stash_t *input1, struct stash_t *input2, int output, int solution)
{
  char i1[MAX_STASH_STRING_LENGTH];
  char i2[MAX_STASH_STRING_LENGTH];
  stash_to_string(input1, i1);
  stash_to_string(input2, i2);
  if (output == solution) {
    printf("\e[1;32mPASSED\e[0m {%s}, {%s}\t output: %d\n", i1, i2, output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m {%s}, {%s}\t output: %d\t solution: %d\n", i1, i2, output, solution);
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
  struct stash_t input[] = {{{1,0,4,3,5}},
                            {{0,10,300,400,9999}},
                            EMPTY_STASH,
                            INFINITE_STEP_STASH
                            };
  for (int i = 0; i < nb_tests; i++) {
    char buffer[MAX_STASH_STRING_LENGTH];
    stash_to_string(&input[i], buffer);
    printf("string stash_t representation: %s\n", buffer);
  }

  printf("Tests on stash_add\n");
  int nb_tests1 = 2;
  struct stash_t inputA[] = {{{1,2,3,4,5}},
                             {{20,99,0,7,51}}
                            };
  struct stash_t inputB[] = {{{1,2,3,4,5}},
                             {{0,3,0,345,54}}
                            };
  struct stash_t solution1[] = {{{2,4,6,8,10}},
                                {{20,102,0,352,105}}
                                };
  for (int i = 0; i < nb_tests1; i++) {
    struct stash_t output = stash_add(&inputA[i], &inputB[i]);
    test_stasht_formated(&output, &solution1[i]);
  }

  printf("Tests on stash_sub\n");
  struct stash_t solution2[] = {{{0,0,0,0,0}},
                                {{20,96,0,0,0}}
                               };
  for (int i = 0; i < nb_tests1; i++) {
    struct stash_t output = stash_sub(&inputA[i], &inputB[i]);
    test_stasht_formated(&output, &solution2[i]);
  }

  printf("Tests on stash_contain\n");
  int nb_tests3 = 3;
  struct stash_t inputA3[] = {{{1,2,3,4,5}},
                             {{1,2,3,4,5}},
                             {{1,2,3,4,5}}
                            };
  struct stash_t inputB3[] = {{{1,2,3,4,5}},
                             {{0,1,3,3,4}},
                             {{2,3,4,6,5}}
                            };
  int solution3[] = {1,1,0};
  for (int i = 0; i < nb_tests3; i++) {
    test_stasht_to_int_formated(&inputA3[i], &inputB3[i], stash_contains(&inputA3[i], &inputB3[i]), solution3[i]);
  }
}
