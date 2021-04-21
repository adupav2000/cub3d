/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:40:14 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/21 12:42:48 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct	s_sprite_print
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

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_data;

typedef struct	s_str
{
	char			*line;
	struct s_str	*next;
}				t_str;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_player
{
	int		position_initialised;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	time;
	double	old_time;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		wallcolor;
	t_img	current_image;
	int		movex;
	int		movey;
	int		rot_left;
	int		rot_right;
	double	wallx;
	int		texnum;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}				t_player;

typedef struct	s_map
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

typedef struct	s_config
{
	int		screenshot;
	char	*prog_name;
	char	*conf_file;
	int		conf_check;
}				t_config;

typedef struct	s_game
{
	t_map			map_info;
	t_player		player;
	t_data			mlx;
	t_config		config;
	t_sprite_print	sprites_p;
}				t_game;
#endif
