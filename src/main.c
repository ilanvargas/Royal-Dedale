#include <stdio.h>
#include "location.h"
#include "dir.h"


int main()
{
    struct location_t res2 = location(4,2);
    struct location_t res = location(4,2);
    int is_valid = location_is_valid(res);
    int is_valid2 = location_is_valid(res2);
    int is_equal = location_equal(res,res2);
    printf("location a is : x = %d, y = %d\n",res.x ,res.y);
    printf("location b is : x = %d, y = %d\n",res2.x ,res2.y);
    printf("location a is valid ? : %d\n", is_valid);
    printf("location b is valid ? : %d\n", is_valid2);
    printf("location a is b ? : %d\n", is_equal);
    return 0;
}

