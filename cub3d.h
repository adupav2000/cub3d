/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:05:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/21 13:05:34 by adu-pavi         ###   ########.fr       */
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
# include "structs.h"

# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

# define X_EVENT_EXIT 17

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

int		parsing(t_game *game, int argc, char **argv);

int		handle_resolution(char *line, t_map *map_info, t_game *game);

int		handle_textures(char **line, t_map *map_info, t_data *data);

int		load_texture(char *tex_link, t_img *img, t_data *mlx);

int		parse_line(char *line, t_data *data, t_map *map_info, t_game *game);

int		handle_colors(char **line, t_map *map_info);

int		parse_map_line(t_game *game, t_map *map, char *line);

char	ft_map(t_str *map, int width, int height);
void	set_wall_color(t_game *game, int x, t_player *play, t_img *tex);
t_img	*get_current_tex(t_game *game);

int		draw_floor_and_ceiling(t_game *game, int x, int y_begin, int len);
int		raycasting(t_game *game);

int		key_press(int key_code, t_game *game);

void	move_forward(t_game *game, t_player *play);
void	move_backward(t_game *game, t_player *play);
void	move_left(t_game *game, t_player *play);
void	move_right(t_game *game, t_player *play);

int		key_release(int key_code, t_game *game);

void	perform_dda(t_game *game);
void	update_pos_view(t_game *game);
void	update_rotation(t_game *game);
void	define_deltadist(t_player *play, int x, t_game *game);
void	define_side_dist(t_game *game);
void	search_wall(t_game *game, t_player *play);
void	get_line_length(t_game *game);

int		everything_was_set(t_map *map_info, t_game *game, int with_map);

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
void	sprite_pixel_put(t_game *game, t_img *tex, int x, int y);
void	sprites_scanner(t_game *game, char *str, int y);
int		save_sprite(int x, int y, t_game *game);
void	check_user_position(t_game *game, char *str, int y);

int		sprite_bubble_sort(t_game *game);
double	get_ss_distance(double posx, double posy, int possx, int possy);
int		set_sprite_distance(t_game *game);

void	set_position(t_game *game, double x, double y);
void	set_plane(t_game *game, double planex, double planey);
int		main(int argc, char **argv);

void	print_all_sprite(t_game *game);
#endif
