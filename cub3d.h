#ifndef CUB3D_H
# define CUB3D_H
#include "minilibx_opengl/mlx.h"
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

typedef struct s_player {
    /*the users position*/
    double posX;
    double posY;
    /*the direction the user is watching*/
    int dirX;
    int dirY;
    /*camera plane of the map*/
    double planeX;
    double planeY;
    /*time of the current frame*/ 
    double time;
    /*time of the old frame*/
    double old_time;
    /*the x-coordinate of */
    /*rays X and Y*/
    double rayDirX;
    double rayDirY;
        


} t_player;


#endif
