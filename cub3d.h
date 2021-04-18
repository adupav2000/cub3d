/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:05:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/16 19:28:12 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "mlx/mlx.h"

# include "libft/libft.h"
# include "utils/keycode_linux.h"

# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

# define X_EVENT_EXIT 17

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}				t_img;

typedef struct	s_sprite
{
	double			posx;
	double			posy;
	double			distance;
	t_img			*tex;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}				t_sprite;

typedef struct s_sprite_print
{
	double	spritex;
	double	spritey;
	double	invdet;
	double	transformx;
	double	transformy;
	int		spritescreenx;
	int		spritewidth;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		drawstartx;
	int		drawendx;
	int		texx;
	int		texy;
	int		texwidth;
	int		texheight;
}				t_sprite_print;

typedef struct data_s
{
	void *mlx_ptr;
	void *mlx_win;
}				t_data;

typedef struct s_str
{
	char			*line;
	struct s_str	*next;
} t_str;

typedef struct s_pos
{
	double x;
	double y;
} t_pos;

typedef struct s_player
{
	int			position_initialised;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		old_time;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			wallcolor;
	t_img		current_image;
	int			movex;
	int			movey;
	int			rot_left;
	int			rot_right;
	double		wallx;
	int			texnum;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
}				t_player;

typedef struct s_map
{
	int			window_height;
	int			window_width;

	int			window_max_height;
	int			window_max_width;

	int			color_floor;
	int			color_ceiling;

	int			te_no_color;
	int			te_so_color;
	int			te_we_color;
	int			te_ea_color;
	int			te_s_color;

	t_img		te_no;
	t_img		te_so;
	t_img		te_we;
	t_img		te_ea;
	t_img		te_s;

	t_str		*plan;
	int			plan_height;
	int			plan_width;

	t_sprite	*sprites;
}				t_map;

typedef struct s_config
{
	int		screenshot;
	char	*prog_name;
	char	*conf_file;
	int		conf_check;
}				t_config;

typedef struct s_game
{
	t_map			map_info;
	t_player		player;
	t_data			mlx;
	t_config		config;
	t_sprite_print	sprites_p;
}				t_game;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

int		parsing(t_game *game, int argc, char **argv);

int		handle_resolution(char *line, t_map *map_info, t_game *game);

int		handle_textures(char **line, t_map *map_info, t_data *data);

int		load_texture(char *tex_link, t_img *img, t_data *mlx);

int		parse_line(char *line, t_data *data, t_map *map_info, t_game *game);

int		handle_colors(char **line, t_map *map_info);

int		parse_map_line(t_game *game, t_map *map, char *line);

char	ft_map(t_str *map, int width, int height);
void	set_wall_color(t_game *game, int x);

int		draw_floor_and_ceiling(t_img img_to_change, int x, int y_begin, int len,
						   t_map *map_info);
int		drawvertlinefromcolor(t_img img_to_change, int x, int y_begin, int len,
						  int color);
int		raycasting(t_game *game);

int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);

void	perform_dda(t_game *game);
void	update_pos_view(t_game *game);
void	update_rotation(t_game *game);
void	define_deltaDist(t_game *game);
void	define_side_dist(t_game *game);
void	search_wall(t_game *game);
void	get_line_length(t_game *game);

int		everything_was_set(t_map *map_info, t_game *game);

void	init_player(t_player *player);
void	init_map(t_map *map_info);
void	init_config(t_config *config);

void	clear_player(t_game *game);
void	clear_mlx(t_data *mlx);
void	clear_map_info(t_game *game);
void	clear_config(t_config *config);
void	clear_all_variables(t_game *game);
int		exit_error(t_game *game, char *message);
int		exit_success(t_game *game);

int		write_and_save_screen(t_game *game);

int		load_color_from_tex(t_img *tex, int x, int y);
void	texture_pixel_put(t_game *game, t_img *tex, int x, int y);
void	sprite_pixel_put(t_game *game, t_img *tex,
			t_sprite_print *sprit, int x, int y);

int		sprite_bubble_sort(t_game *game);
double	get_ss_distance(double posX, double posY, int posSX, int posSY);
int		set_sprite_distance(t_game *game);

int		main(int argc, char **argv);

void	print_all_sprite(t_game *game);
#endif
