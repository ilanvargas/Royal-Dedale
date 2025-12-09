#include <stdio.h>
#include <string.h>
#include <string.h>
#include "tile.h"


#ifndef TILES_NUMBER
#define TILES_NUMBER 3
#endif

#ifndef MAX_TILE_NAME_LEGTH
#define MAX_TILE_NAME_LENGTH 40
#endif


void print_stash(struct stash_t* stash)
{
  for (int i = 0; i <= NUM_RESOURCES; i++)
    printf("%s:%d ", resource_to_short_string(i), (unsigned int)stash->r[i]);
  printf("\n");
}

int equal_stash(struct stash_t* a, struct stash_t* b)
{
  for (int i = 1; i <= NUM_RESOURCES; i++)
    if (a->r[i] != b->r[i]) return 0;
  return 1;
}

void print_tile(const struct tile_t* tile)
{
  printf("%s\n", tile_name(tile));
  char ch[MAX_STASH_STRING_LENGTH];
  struct stash_t tr = tile_traversal_cost(tile);
  stash_to_string(&tr, ch);
  printf("traversal cost: %s, \n", ch);
  printf("opening cost in:\n");
  for (int i = 0; i < MAX_DIRS; i++)
  {
    printf("%s: ", dir_to_short_string(i));
    char sh[MAX_STASH_STRING_LENGTH];
    struct stash_t op = tile_opening_cost(tile, i);
    stash_to_string(&op, sh);
    printf("%s\n", sh);
  }
}

void print_tile_array(int size, struct tile_t* array[])
{
  for (int i = 0; i < size; i++)
  {
    print_tile(array[i]);
  }
}

void tests_tile()
{
  printf("\n");
  printf("\e[1mTESTS ON tile.c\e[0m\n");

  printf("\nTest on tile_generate_empty\n");
  printf("input tile name to be generated : %s\n", "empty");
  const struct tile_t* input1 = tile_generate_empty();
  print_tile(input1);
  printf("Test on tile_generate_start\n");
  printf("input tile name to be generated : %s\n", "start");
  const struct tile_t* input2 = tile_generate_start();
  print_tile(input2);
  printf("Test on tile_generate_exit\n");
  printf("input tile name to be generated : %s\n", "exit");
  const struct tile_t* input3 = tile_generate_exit();
  print_tile(input3);

  printf("\nTests on tile_generate_by_name\n");
  int nb_tests4 = 3;
  const char* input4[] = {"cloister", "ew corridor", "s terrace" };
  for (int i = 0; i < nb_tests4; i++)
  {
    const struct tile_t* by_name = tile_generate_by_name(input4[i]);
    printf("input tile name to be generated : %s\n", input4[i]);
    print_tile(by_name);
  }

  const struct tile_t* empty_t = tile_generate_empty();
  const struct tile_t* start_t = tile_generate_start();
  const struct tile_t* exit_t = tile_generate_exit();
  char* tile_names[] = {"terrace", "corridor", "cloister" };
  const struct tile_t* tiles[TILES_NUMBER];
  for (int i = 0; i < TILES_NUMBER; i++)
  {
    tiles[i] = tile_generate_by_name(tile_names[i]);
  }
  
  printf("\nTests on tile_draft\n");
  init_tiles(2);
  struct tile_t* results[NUM_TILES_PER_TURN];
  enum dir_t d_raft = NORTH;
  unsigned int output = tile_draft(d_raft, results);
  print_tile_array(output, results);

  printf("\nTests on tile_can_open");
  int nb_tests5 = 5;
  const struct tile_t* input5[] = { empty_t, start_t, exit_t, tiles[1], tiles[1] };
  enum dir_t d5[] = {SOUTH, WEST, EAST, NORTH, WEST};
  for (int i = 0; i < nb_tests5; i++)
  {
    int output5 = tile_can_open(input5[i], d5[i]);
    printf("\ninput tile: ");
    print_tile(input5[i]);
    printf("\n output: %d\n", output5);
  }
}
