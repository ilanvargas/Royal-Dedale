#ifndef __DEDALE_TEST_H__
#define __DEDALE_TEST_H__

/** Compare the output of a function X->string to the soluion (X:char/small int/enum)
 * return bool value and print the result of the test */
int test_X_to_str(void *input, const char *output, char *solution);

// Test of a function X->X
int test_X_to_X(void *input, const void *output, void *solution);

#endif
