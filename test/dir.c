#include "../src/dir.c"
#include <stdio.h>

int main(int argc, char *argv[])
{
  printf("TEST SUR dir.c\n");
  printf("TEST SUR dir_to_tring\n");
  printf("%s\n", dir_to_string(NORTH));
  printf("%s\n", dir_to_string(EAST));
  printf("%s\n", dir_to_string(SOUTH));
  printf("%s\n", dir_to_string(INVALID_DIR));
  printf("%s\n", dir_to_string(MAX_DIRS));

  printf("TEST SUR dir_to_short_string\n");
  printf("%s\n", dir_to_short_string(NORTH));
  printf("%s\n", dir_to_short_string(EAST));
  printf("%s\n", dir_to_short_string(SOUTH));
  printf("%s\n", dir_to_short_string(INVALID_DIR));
  printf("%s\n", dir_to_short_string(MAX_DIRS));
  
  printf("TEST SUR dir_opposite\n");
  printf("%d\n", dir_opposite(NORTH));
  printf("%d\n", dir_opposite(EAST));
  printf("%d\n", dir_opposite(SOUTH));
  printf("%d\n", dir_opposite(MAX_DIRS));
}
