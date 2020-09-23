#include "structs.h"

int init_t_player(t_player *to_init)
{
    to_init->posX = 10;
    to_init->posY = 10;
    
    to_init->dirX = -1;
    to_init->dirY = 0;

    to_init->planeX = 0;
    to_init->planeY = 0.66;

    to_init->time = 0;
    to_init->old_time = 0;

    
    return (1);
}
