/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:15:34 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 18:25:20 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_pixel_put(t_game *game, t_img *tex, int x, int y)
{
	t_img			*curr_img;
	t_sprite_print	*sprit;
	int				r;
	int				g;
	int				b;

	curr_img = &(game->player.current_image);
	sprit = &(game->sprites_p);
	r = tex->addr[sprit->texy * tex->line_length
		+ sprit->texx * (tex->bpp / 8)];
	g = tex->addr[sprit->texy * tex->line_length
		+ sprit->texx * (tex->bpp / 8) + 1];
	b = tex->addr[sprit->texy * tex->line_length
		+ sprit->texx * (tex->bpp / 8) + 2];
	if (!((r & 0x00FFFFFF) == 0
			&& (g & 0x00FFFFFF) == 0 && (b & 0x00FFFFFF) == 0))
	{
		curr_img->addr[y * curr_img->line_length
			+ x * curr_img->bpp / 8] = r;
		curr_img->addr[y * curr_img->line_length
			+ x * curr_img->bpp / 8 + 1] = g;
		curr_img->addr[y * curr_img->line_length
			+ x * curr_img->bpp / 8 + 2] = b;
	}
}

void	texture_pixel_put(t_game *game, t_img *tex, int x, int y)
{
	t_img	*curr_img;

	curr_img = &(game->player.current_image);
	curr_img->addr[y * curr_img->line_length + x * curr_img->bpp / 8]
		= tex->addr[game->player.texy * tex->line_length
		+ game->player.texx * (tex->bpp / 8)];
	curr_img->addr[y * curr_img->line_length
		+ x * curr_img->bpp / 8 + 1]
		= tex->addr[game->player.texy * tex->line_length
		+ game->player.texx * (tex->bpp / 8) + 1];
	curr_img->addr[y * curr_img->line_length
		+ x * curr_img->bpp / 8 + 2]
		= tex->addr[game->player.texy * tex->line_length
		+ game->player.texx * (tex->bpp / 8) + 2];
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	draw_floor_and_ceiling(t_game *game, int x, int y_begin, int len)
{
	int		i;
	t_map	*map_info;
	t_img	*img_to_change;

	map_info = &(game->map_info);
	img_to_change = &(game->player.current_image);
	i = 0;
	if ((x > img_to_change->width) || (x < 0) || (y_begin < 0)
		|| (len < 0) || ((len + y_begin) > img_to_change->height))
		return (-1);
	while (i < y_begin)
		my_mlx_pixel_put(&img_to_change, x, i++, map_info->color_ceiling);
	i += len;
	while (i < map_info->window_height)
		my_mlx_pixel_put(&img_to_change, x, i++, map_info->color_floor);
	return (0);
}
