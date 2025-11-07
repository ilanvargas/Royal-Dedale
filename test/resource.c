#include <stdio.h>
#include "resource.h"


int main()
{
    const char *res = resource_to_string(KEY);
    const char *r = resource_to_short_string(KEY);
    printf("la ressource est : %s\nversion courte de la ressource : %s\n", res, r);
    return 0;
}