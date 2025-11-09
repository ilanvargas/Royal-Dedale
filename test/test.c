#include <stdio.h>
#include <string.h>

int test_X_to_str(void *input, const char *output, char *solution)
{
  char i = *(char *)input;

  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: %d\t output: %s\n", i, output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %d\t output: %s\t solution: %s\n", i, output, solution);
    return 0;
  }
}

int test_X_to_X(void *input, const void *output, void *solution)
{
  char i = *(char *)input;
  char o = *(char *)output;
  char s = *(char *)solution;

  if (!strcmp(output, solution)) {
    printf("\e[1;32mPASSED\e[0m input: %d\t output: %d\n", i, o);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m input: %d\t output: %d\t solution: %d\n", i, o, s);
    return 0;
  }
}
