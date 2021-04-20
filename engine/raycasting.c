/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 19:00:49 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_verical_stripes(t_game *game, double zbuffer[10000],
		int stripe, t_sprite_print *sprit)
{
	int				y;
	int				d;

	while (stripe < sprit->drawendx)
	{
		sprit->texx = (int)(256 * (stripe - (-sprit->spritewidth / 2
						+ sprit->spritescreenx))
				* sprit->texwidth / sprit->spritewidth) / 256;
		if (sprit->transformy > 0 && stripe > 0
			&& stripe < game->map_info.window_width
			&& sprit->transformy < zbuffer[stripe])
		{
			y = sprit->drawstarty;
			while (y < sprit->drawendy)
			{
				d = (y) * 256 - game->map_info.window_height
					* 128 + sprit->spriteheight * 128;
				sprit->texy = ((d * sprit->texheight)
						/ sprit->spriteheight) / 256;
				sprite_pixel_put(game, &game->map_info.te_s, stripe, y);
				y++;
			}
		}
		stripe++;
	}
}

void	set_sprite_p_and_ht(t_player *play,
	t_game *game,
	t_sprite_print *sprit,
	t_sprite *sprite)
{
	sprit->transformx = sprit->invdet * (play->diry * sprit->spritex
			- play->dirx * sprit->spritey);
	sprit->transformy = sprit->invdet * (-play->planey * sprit->spritex
			+ play->planex * sprit->spritey);
	sprit->spritescreenx = (int)((game->map_info.window_width / 2)
			* (1 + sprit->transformx / sprit->transformy));
	sprit->spriteheight = abs((int)(game->map_info.window_height
				/ sprit->transformy));
	sprit->drawstarty = -sprit->spriteheight / 2
		+ game->map_info.window_height / 2;
	if (sprit->drawstarty < 0)
		sprit->drawstarty = 0;
	sprit->drawendy = sprit->spriteheight / 2
		+ game->map_info.window_height / 2;
	if (sprit->drawendy >= game->map_info.window_height)
		sprit->drawendy = game->map_info.window_height - 1;
	sprit->spritewidth = abs((int)(game->map_info.window_height
				/ (sprit->transformy)));
	sprit->drawstartx = -sprit->spritewidth / 2 + sprit->spritescreenx;
	if (sprit->drawstartx < 0)
		sprit->drawstartx = 0;
	sprit->drawendx = sprit->spritewidth / 2 + sprit->spritescreenx;
	if (sprit->drawendx >= game->map_info.window_width)
		sprit->drawendx = game->map_info.window_width - 1;
}

void	set_sprite(t_game *game, double ZBuffer[10000], t_sprite *sprite)
{
	t_player		*play;
	t_sprite_print	*sprit;

	if (set_sprite_distance(game))
		exit_error(game, "failed at sorting the sprites");
	play = &(game->player);
	sprit = &(game->sprites_p);
	while (sprite != NULL)
	{
		sprit->spritex = sprite->posx - play->posx;
		sprit->spritey = sprite->posy - play->posy;
		sprit->texwidth = game->map_info.te_s.width;
		sprit->texheight = game->map_info.te_s.height;
		sprit->invdet = 1.0 / (play->planex * play->diry
				- play->dirx * play->planey);
		set_sprite_p_and_ht(play, game, sprit, sprite);
		write_verical_stripes(game, ZBuffer,
			(game->sprites_p.drawstartx), &(game->sprites_p));
		sprite = sprite->next;
	}
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win,
		play->current_image.img, 0, 0);
	mlx_destroy_image(game->mlx.mlx_ptr, play->current_image.img);
	play->current_image.img = NULL;
	play->current_image.addr = NULL;
}

int	init_mlx_obj(t_player *play, t_game *game)
{
	play->current_image.img = mlx_new_image(game->mlx.mlx_ptr,
			game->map_info.window_width, game->map_info.window_height);
	if (play->current_image.img == NULL)
		return (-1);
	play->current_image.height = game->map_info.window_height;
	play->current_image.width = game->map_info.window_width;
	play->current_image.addr = mlx_get_data_addr(play->current_image.img,
			&play->current_image.bpp, &play->current_image.line_length,
			&play->current_image.endian);
	if (play->current_image.addr == NULL)
		return (-1);
	return (0);
}

int	raycasting(t_game *game)
{
	int			x;
	t_player	*play;
	double		zbuffer[10000];

	play = &(game->player);
	if (init_mlx_obj(play, game))
		return (exit_error(game, "malloc error raycast"));
	x = 0;
	while (x < game->map_info.window_width)
	{
		play->camerax = (2 * x / (double)game->map_info.window_width) - 1;
		define_deltadist(&(game->player));
		define_side_dist(game);
		search_wall(game, play);
		get_line_length(game);
		set_wall_color(game, x, &(game->player), get_current_tex(game));
		if (draw_floor_and_ceiling(game, x, play->drawstart,
				(play->drawend - play->drawstart)))
			break ;
		zbuffer[x++] = play->perpwalldist;
	}
	set_sprite(game, (double *)(zbuffer), (game->map_info.sprites));
	update_pos_view(game);
	update_rotation(game);
	return (0);
}
