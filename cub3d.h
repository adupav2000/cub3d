/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:05:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/14 12:09:25 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "mlx/mlx.h"

#include "libft/libft.h"
#include "utils/keycode_macos.h"

#define MLX_SYNC_IMAGE_WRITABLE    1
#define MLX_SYNC_WIN_FLUSH_CMD     2
#define MLX_SYNC_WIN_CMD_COMPLETED 3

#define X_EVENT_EXIT 17


typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bpp;
    int         line_length;
    int         width;
    int         height;
    int         endian;
}               t_img;

typedef struct	s_sprite
{
	double			    posX;
    double             posY;
	double			distance;
	t_img			*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}	t_sprite;

typedef struct s_sprite_print  
{
   /*sprite vars*/
    double spriteX;
    double spriteY;
    double invDet;
    double transformX;
    double transformY;
    int     spriteScreenX;
    int     spriteWidth;
    int     spriteHeight;
    int     drawStartY;
    int     drawEndY;
    int     drawStartX;
    int     drawEndX;
    int     texX;
    int     texY;
    int     texWidth;
    int     texHeight;
} t_sprite_print;

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 t_data;

typedef struct s_str{
   char          *line;
   struct s_str  *next;
}   t_str;

typedef struct s_pos{
    double  x;
    double  y;
} t_pos;

typedef struct s_player {
    int position_initialised;
    /*the users position*/
    double posX;
    double posY;
    /*the direction the user is watching*/
    double dirX;
    double dirY;
    /*camera plane of the map*/
    double planeX;
    double planeY;
    /*time of the current frame*/ 
    double time;
    /*time of the old frame*/
    double old_time;
    /*the x-coordinate of */
    double cameraX;
    /*rays X anarwsind Y*/
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
    t_img current_image;
    /*MOVING AND ROTATING VARIABLES*/
    /*these variables tell if the player is holding a key_down*/
	/*move forward : moveX = 1*/
    /*move backward : moveX = -1*/
    int moveX;
    int moveY;
    /*rotation variables*/
    int rot_left;
    int rot_right;
    /*where exactly the wall was hit*/
    double wallX;
    /*texturing calculation*/
    int texNum;
    int texX;
    int texY;
    /*how much to incerease the texture coordinate per screen pixel*/
    double step;
    double texPos;
 } t_player;

typedef struct s_map{   
    int     window_height;
    int     window_width;

	int     window_max_height;
    int     window_max_width;

    int     color_floor;
    int     color_ceiling;

    int     te_no_color;
    int     te_so_color;
    int     te_we_color;
    int     te_ea_color;
    int     te_s_color;

    t_img   te_no;
    t_img   te_so;
    t_img   te_we;
    t_img   te_ea;
    t_img   te_s;

    t_str   *plan;
    int     plan_height;
    int     plan_width;

    t_sprite	*sprites;
} t_map;

typedef struct s_config{
    int     screenshot;
    char    *prog_name;
    char    *conf_file;
} t_config;

typedef struct s_game{
    t_map           map_info;
    t_player        player;
    t_data          mlx;
    t_config        config;
    t_sprite_print  sprites_p;
} t_game;

void            my_mlx_pixel_put(t_img *data, int x, int y, int color);
    
int     parsing(t_game *game, int argc, char **argv);

int     handle_resolution(char *line, t_map *map_info, t_game *game);

int     handle_textures(char **line, t_map *map_info, t_data *data);

int     load_texture(char *tex_link, t_img *img, t_data *mlx);

int     parse_line(char *line, t_data *data, t_map *map_info, t_game *game);

int     handle_colors(char **line, t_map *map_info);

int     parse_map_line(t_game *game, t_map *map, char *line);

char    ft_map(t_str *map, int width, int height);
void    set_wall_color(t_game *game, int x);

int    draw_floor_and_ceiling(t_img img_to_change, int x, int y_begin, int len,
            t_map *map_info);
int     drawVertLineFromColor(t_img img_to_change, int x, int y_begin, int len, 
            int color);
int     raycasting(t_game *game);

int     key_press(int key_code, t_game *game);
int     key_release(int key_code, t_game *game);

void    perform_dda(t_game *game);
void    update_pos_view(t_game *game);
void    update_rotation(t_game *game);

int     everything_was_set(t_map *map_info, t_game *game);

void    init_player(t_player *player);
void    init_map(t_map *map_info);

/*all exit and clearing functions*/
void    clear_player(t_player *player);
void    clear_mlx(t_data *mlx);
void    clear_map_info(t_map *map_info);
void    clear_config(t_config *config);
void    clear_all_variables(t_game *game);
int     exit_error(t_game *game, char *message);
int     exit_success(t_game *game);

int     write_and_save_screen(t_game *game);

int load_color_from_tex(t_img *tex, int x, int y);
void texture_pixel_put(t_game *game, t_img *tex, int x, int y);
void sprite_pixel_put(t_game *game, t_img *tex, int x, int y);

int sprite_bubble_sort(t_game *game);
double get_ss_distance(double posX, double posY, int posSX, int posSY);
int set_sprite_distance(t_game *game);

/*main function*/
int     main(int argc, char **argv);

void print_all_sprite(t_game *game);
#endif
