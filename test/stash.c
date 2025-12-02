#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stash.h"


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
