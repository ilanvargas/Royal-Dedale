#include "tile_bis.h"
#include <stdio.h>

#define NUM_DRAFTS 7
#define MAX_TILES 21

unsigned int draft(enum dir_t d, struct tile_bis_t results[MAX_TILES])
{
    unsigned int i = 0;
    struct tile_t* res[MAX_TILES];
    unsigned int c = tile_draft(d, res);
    unsigned int j = 0;
    for(int k = 0; k < NUM_DRAFTS; k++)
    {
        while(i < MAX_TILES && j < c)
        {
            for (int r = 0; r < NB_ROT; r++)
            {
                if (tile_can_open(res[i], ROT_TO_DIR(d,r)))
                {
                    results[i].tile = res[j];
                    results[i].rot = r;
                }
            }
            j++;
        }
    }
    return i;
}

int main()
{
    struct tile_bis_t results[MAX_TILES];
    unsigned int len = draft(NORTH, results);
    for (unsigned int i = 0; i < len; i++)
        printf("[tile: %s ,rotation: %d]", tile_name(results[i].tile),results[i].rot);
    printf("\n");
    return 0;
}
