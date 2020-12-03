#ifndef CUB3D_H
# define CUB3D_H
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "mlx/mlx.h"

#include "libft/libft.h"

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

typedef struct s_map{
    int window_height;
    int window_width;

    int     color_floor;
    int     color_ceiling;

    void    *te_no;
    int     te_no_width;
    int     te_no_height;

    void    *te_so;
    int     te_so_width;
    int     te_so_height;

    void    *te_we;
    int     te_we_width;
    int     te_we_height;
    
    void    *te_ea;
    int     te_ea_width;
    int     te_ea_height;

    void    *te_s;
    int     te_s_width;
    int     te_s_height;
    
    char    **plan;
} t_map;

int     parsing(t_map *map_info, data_t *date);
int     handle_resolution(char **line, t_map *map_info);
int     handle_textures(char **line, t_map *map_info, data_t *data);
#endif
