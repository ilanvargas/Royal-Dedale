#include <stdio.h>
#include "location.h"

int test_location(unsigned int input1, unsigned int input2, struct location_t output, struct location_t solution)
{
    if (output.x == solution.x && output.y == solution.y)
    {
      printf("\e[1;32mPASSED\e[0m input: %d, %d\t output: {%d, %d}\n",input1, input2, output.x, output.y);
      return 1;
    }
    else
    {
      printf("\e[1;31mFAILED\e[0m input: %d, %d\t output: {%d, %d}\t solution: {%d, %d}\n", input1, input2, output.x, output.y, solution.x, solution.y);
      return 0;
    }
}

int test_location_is_valid(struct location_t input, int output, int solution)
{
    if (output == solution)
    {
      printf("\e[1;32mPASSED\e[0m input: {%d, %d}\t output: %d\n", input.x, input.y, output);
      return 1;
    }
    else 
    {
      printf("\e[1;31mFAILED\e[0m input: {%d, %d}\t output: %d\t solution: %d\n", input.x, input.y, output, solution);
      return 0;
    }
}

int test_location_equal(struct location_t input1, struct location_t input2, int output, int solution)
{
    if (output == solution) {
      printf("\e[1;32mPASSED\e[0m inputs: {%d, %d}, {%d, %d}\t output: %d\n", input1.x, input1.y, input2.x, input2.y, output);
      return 1;
    } 
    else {
      printf("\e[1;31mFAILED\e[0m inputs: {%d, %d}, {%d, %d}\t output: %d\t solution: %d\n", input1.x, input1.y, input2.x, input2.y, output, solution);
      return 0;
    }
}

int test_location_is_adjacent(struct location_t input1, struct location_t input2, int output, int solution)
{
    if (output == solution) {
      printf("\e[1;32mPASSED\e[0m inputs: {%d, %d}, {%d, %d}\t output: %d\n", input1.x, input1.y, input2.x, input2.y, output);
      return 1;
    } 
    else {
      printf("\e[1;31mFAILED\e[0m inputs: {%d, %d}, {%d, %d}\t output: %d\t solution: %d\n", input1.x, input1.y, input2.x, input2.y, output, solution);
      return 0;
    }
}


void tests_location()
{
    printf("\n");
    printf("\e[1mTESTS ON location.c\e[0m\n");
    
    printf("Tests on location \n");
    int nb_tests1 = 2;
    unsigned int input0[] = {2,3};
    unsigned int input1[] = {4,1};
    struct location_t solution1[] = {{2,4},{3,1}};
    for (int i = 0; i < nb_tests1; i++)
    {
      struct location_t output1 = location(input0[i], input1[i]);
      test_location(input0[i], input1[i], output1, solution1[i]);
    }

    printf("Tests on location is valid\n");
    int nb_tests2 = 4;
    struct location_t input2[] = { {0,4},{1,5},{2,2},{3,2} };
    int solution2[] = {1, 0, 1, 0};
    for (int i = 0; i < nb_tests2; i++)
    {
      int output2 = location_is_valid(input2[i]);
      test_location_is_valid(input2[i], output2, solution2[i]);
    }

    printf("Tests on location_equal\n");
    int nb_tests3 = 4;
    struct location_t input3[] = { {2, 3}, {0,1}, {1,4}, {2,2} };
    struct location_t input4[] = { {2, 3}, {2,1}, {1,3}, {1,1} };
    int solution3 [] = {1, 0, 0, 0};
    for (int i = 0; i < nb_tests3; i++)
    {
      int output3 = location_equal(input3[i], input4[i]);
      test_location_equal(input3[i], input4[i], output3, solution3[i]);
    }

    printf("Tests on location_is_adjacent\n");
    int nb_tests5 = 4;
    struct location_t input5[] = { {2, 3}, {0,1}, {1,4}, {1,2} };
    struct location_t input6[] = { {2, 2}, {1,1}, {1,4}, {0,1} };
    int solution5 [] = {1, 1, 0, 0};
    for (int i = 0; i < nb_tests5; i++)
    {
      int output5 = location_is_adjacent(input5[i], input6[i]);
      test_location_is_adjacent(input5[i], input6[i], output5, solution5[i]);
    }
}


