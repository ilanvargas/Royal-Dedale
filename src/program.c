#include "tile_bis.h"
#include <stdio.h>

#define NUM_DRAFTS 7
#define MAX_TILES 21

void draft(enum dir_t d, struct tile_bis_t* results)
{
    for(int k = 0; k < NUM_DRAFTS; k++)
    {
        struct tile_t* res[MAX_TILES];
        unsigned int c = tile_draft(NORTH, res);
        int i = 0;
        while(i < MAX_TILES)
        {
            for (int r = 0; i < NB_ROT; r++)
            {
                if (tile_can_open(res[i], ROT_TO_DIR(d,r)))
                    results[i].tile = res[] 
            }
        }
    }
}