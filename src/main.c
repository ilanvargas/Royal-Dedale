#include <stdio.h>
#include "location.h"
#include "resource.h"


int main()
{
    const char *res = resource_to_string(GOLD);
    printf("la ressource est : %s\n", res);
    return 0;
}