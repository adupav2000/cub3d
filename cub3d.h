/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:05:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2020/12/23 15:20:01 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "mlx/mlx.h"

#define MLX_SYNC_IMAGE_WRITABLE    1 
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

# include "libft/libft.h"
# include "config/parsing.h"

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bpp;
    int         line_length;
    int         width;
    int         height;
    int         endian;
}               t_img;

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 t_data;

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
    double cameraX;
    /*rays X and Y*/
    double rayDirX;
    double rayDirY;
    /*position in the map out of context*/
    int mapX;
    int mapY;
    /*distance to the first next wall(x-side or y-side)*/
    double sideDistX;
    double sideDistY;
    /*length between two sides*/
    double deltaDistX;
    double deltaDistY;
    /*used to calculate the length of the ray*/
    double perpWallDist;
    /*get the direction of the steps*/
    int stepX;
    int stepY;
    /*if a wall was hit*/
    int hit;
    /*which side of the wall was hit*/
    int side;
    /*height that will be drawn on the screen*/
    int lineHeight; 
    int drawStart;
    int drawEnd;
    /*color of the wall that is being drawn right after*/
    int wallColor;
    /*Image used as buffer to be written in the page*/
    t_img *current_image;
} t_player;

typedef struct s_map{
    int window_height;
    int window_width;
    int     color_floor;
    int     color_ceiling;
    t_img   te_no;
    t_img   te_so;
    t_img   te_we;
    t_img   te_ea;
    t_img   te_s;
    char    **plan;
    int     plan_height;
} t_map;

typedef struct s_game{
    t_map       *map_info;
    t_player    *player;
    t_data      *mlx;
} t_game;

void            my_mlx_pixel_put(t_img *data, int x, int y, int color);
    
int     parsing(t_game *game);
int     handle_resolution(char *line, t_map *map_info);
int     handle_textures(char **line, t_map *map_info, t_data *data);
int     load_texture(char *tex_link, t_img *img, t_data *mlx);
int     parse_line(char *line, t_data *data, t_map *map_info);
int     handle_colors(char **line, t_map *map_info);
int     parse_map_line(t_map *map, char *line);

int     drawVertLineFromColor(t_img *img_to_change, int x, int y_begin, int len, 
            int color);
int     raycasting(t_game *game);
#endif
