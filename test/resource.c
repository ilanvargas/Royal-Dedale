#include <stdio.h>
#include "../src/resource.h"


void tests_resource()
{
    printf("\n");
    printf("\e[1mTESTS ON resource.c\e[0m\n");
    printf("Tests on resource_to_string \n");
    const char *res = resource_to_string(KEY);
    printf("Tests on resource_to_short_string \n");
    const char *r = resource_to_short_string(KEY);
    printf("la ressource est : %s\nversion courte de la ressource : %s\n", res, r);
}