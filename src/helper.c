#include "tile_bis.h"
#include <stdio.h>

#define NUM_DRAFTS 7
#define MAX_TILES 21

unsigned int draft(enum dir_t d, struct tile_bis_t results[MAX_TILES])
{
    struct tile_bis_t res[MAX_TILES];
    unsigned int results_len = 0;
    for (int i = 0; i < NUM_DRAFTS; i++) { 
      unsigned int c = tile_draft_bis(dir_opposite(d), INFINITE_STEP_STASH, res);
      for (unsigned int j = 0; j < c; j++) {
	results[results_len] = res[j];
	results_len ++;
      }
    }
    return results_len;
}

int main()
{
    struct tile_bis_t results[MAX_TILES];
    unsigned int len = draft(NORTH, results);
    printf("%d\n", len);
    for (unsigned int i = 0; i < len; i++)
        printf("[tile: %s ,rotation: %d]", tile_name(results[i].tile),results[i].rot);
    printf("\n");
    return 0;
}
