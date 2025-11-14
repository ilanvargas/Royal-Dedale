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
