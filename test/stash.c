#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stash.h"

//Test fonctions
/* int test_stasht_formated(struct stash_t *output, struct stash_t *solution)
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
*/
void print_stash_n(const struct stash_t stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s:%d ", resource_to_short_string(i), (unsigned int)stash.r[i]);
  printf("\n");
}
void print_stash_p(const struct stash_t* stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s:%d ", resource_to_short_string(i), (unsigned int)stash->r[i]);
  printf("\n");
}

struct stash_t generate_stash()
{
  struct stash_t stash;
  stash.r[0] = 0;
  for (int i = 1; i <= NUM_RESOURCES; i++)
  {
    stash.r[i] = rand()%10; 
  }
  return stash;
}

//Tests
void tests_stash()
{
  srand(8);
  printf("\n");
  printf("\e[1mTESTS ON stash.c\e[0m\n");
  const struct stash_t s1 = generate_stash();
  const struct stash_t s2 = generate_stash();
  const struct stash_t s3 = generate_stash();
  const struct stash_t s4 = generate_stash();
  printf("\nTests on stash_to_string\n");
  int nb_tests = 4;
  const struct stash_t* input[] = {&s1,
                            &s2,
                            &EMPTY_STASH,
                            &INFINITE_STEP_STASH
                            };
  for (int i = 0; i < nb_tests; i++) {
    char buffer[MAX_STASH_STRING_LENGTH];
    stash_to_string(input[i], buffer);
    printf("input stash: \n");
    print_stash_p(input[i]);
    printf("string stash_t representation: %s\n", buffer);
  }

  printf("\nTests on stash_add\n");
  int nb_tests1 = 2;
  const struct stash_t* inputA[] = {&s2,&s4};
  const struct stash_t* inputB[] = {&s1,&s3};
  for (int i = 0; i < nb_tests1; i++) {
    struct stash_t output = stash_add(inputA[i], inputB[i]);
    printf("input stashes:\n");
    print_stash_p(inputA[i]);
    print_stash_p(inputB[i]);
    printf("output stash:\n");
    print_stash_n(output);
    
  }

  printf("\nTests on stash_sub\n");
  for (int i = 0; i < nb_tests1; i++) {
    struct stash_t output = stash_sub(inputA[i], inputB[i]);
    printf("input stashes:\n");
    print_stash_p(inputA[i]);
    print_stash_p(inputB[i]);
    printf("output stash:\n");
    print_stash_n(output);
  }

  printf("\nTests on stash_contains\n");
  const struct stash_t* inputA3 = &s1;
  const struct stash_t* inputB3 = &s2;
  
  int output3 = stash_contains(inputA3, inputB3);
  printf("input stashes:\n");
  print_stash_p(inputA3);
  print_stash_p(inputB3);
  printf("output : %d\n", output3);
}
