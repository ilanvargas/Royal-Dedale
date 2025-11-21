#include <stdio.h>
#include "../src/resource.h"
#include <string.h>

int test_resource(enum resource_t input, const char* output, const char* solution)
{
    if (!strcmp(output, solution))
    {
        printf("\e[1;32mPASSED\e[0m input: %3d\t output: %s\n", input, output);
        return 1;
    }
    else {
        printf("\e[1;31mFAILED\e[0m input: %3d\t output: %s\t solution: %s\n", input, output, solution);
        return 0;
    }
}
void tests_resource()
{
    printf("\n");
    printf("\e[1mTESTS ON resource.c\e[0m\n");

    printf("Tests on resource_to_string \n");
    int nb_tests = 5;
    enum resource_t input[] = {NOTHING, STEP, SILK, OIL, CRYSTAL};
    const char* solution[] = {"NOTHING", "STEP", "SILK", "OIL", "CRYSTAL"};
    for (int i = 0; i < nb_tests; i++)
    {
        const char* output = resource_to_string(input[i]);
        test_resource(input[i], output, solution[i]);
    }

    printf("Tests on resource_to_short_string \n");
    int nb_tests2 = 4;
    enum resource_t input2[] = {NOTHING, STEP, GOLD, CRYSTAL};
    const char* solution2[] = {"N", "St", "Gd", "C"};
    for (int i = 0; i < nb_tests2; i++)
    {
        const char *output2 = resource_to_short_string(input2[i]);
        test_resource(input2[i], output2, solution2[i]);
    }
}
