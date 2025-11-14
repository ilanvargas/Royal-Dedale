#include <stdio.h>
#include "../src/location.h"

int main()
{
    struct location_t res2 = location(2,5);
    struct location_t res = location(1,4);
    int is_valid = location_is_valid(res);
    int is_valid2 = location_is_valid(res2);
    int is_equal = location_equal(res,res2);
    int is_adjacent = location_is_adjacent(res, res2);
    printf("location a is : x = %d, y = %d\n",res.x ,res.y);
    printf("location b is : x = %d, y = %d\n",res2.x ,res2.y);
    printf("location a is valid ? : %d\n", is_valid);
    printf("location b is valid ? : %d\n", is_valid2);
    printf("location a is b ? : %d\n", is_equal);
    printf("locations a and b are adjacent ? : %d\n", is_adjacent);
    return 0;
}

int test_location_is_valid(const int output, const int solution)
{
    if (output == solution) {
    printf("\e[1;32mPASSED\e[0m output: %d\n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: %d\t solution: %d\n", output, solution);
    return 0;
  }
}

int test_location_equal(const int output, const int solution)
{
    if (output == solution) {
    printf("\e[1;32mPASSED\e[0m output: %s\n", output);
    return 1;
  } else {
    printf("\e[1;31mFAILED\e[0m output: %s\t solution: %s\n", output, solution);
    return 0;
  }
}

