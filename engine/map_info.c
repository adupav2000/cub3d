/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:30:18 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/19 19:22:14 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	ft_map(t_str *map, int width, int height)
{
	while (map && (--height > 0))
		map = map->next;
	if (map && width <= (int)ft_strlen(map->line))
	{
		if (map->line[width] == ' ')
			return ('1');
		return (map->line[width]);
	}
	return (-1);
}

static t_img	*get_current_tex(t_game *game)
{
	t_player	*play;
	t_img		*tex;

	play = &(game->player);
	tex = &(game->map_info.te_we);
	if (play->side == 1)
		tex = &(game->map_info.te_no);
	else if (play->side == 2)
		tex = &(game->map_info.te_so);
	else if (play->side == 3)
		tex = &(game->map_info.te_ea);
	return (tex);
}

void	set_wall_color_precalculation(t_game *game,
		int x,
		t_player *play,
		t_img *tex)
{
	if (play->side == 0 || play->side == 1)
		play->wallx = play->posy + play->perpwalldist * play->raydiry;
	else
		play->wallx = play->posx + play->perpwalldist * play->raydirx;
	play->wallx -= floor(play->wallx);
	play->texx = (int)(play->wallx * (double)tex->width);
	if (play->side == 0 && play->raydirx > 0)
		play->texx = tex->width - play->texx - 1;
	if (play->side == 1 && play->raydiry < 0)
		play->texx = tex->width - play->texx - 1;
	play->step = 1.0 * tex->height / play->lineheight;
	play->texpos = (play->drawstart - game->map_info.window_height / 2
			+ play->lineheight / 2) * play->step;
}

void	set_wall_color(t_game *game, int x)
{
	t_player		*play;
	int				y;
	unsigned int	color;
	t_img			*tex;

	play = &(game->player);
	tex = get_current_tex(game);
	set_wall_color_precalculation(game, x, play, tex);
	y = play->drawstart;
	while (y < play->drawend)
	{
		play->texy = (int)play->texpos & (tex->height - 1);
		play->texpos += play->step;
		texture_pixel_put(game, tex, x, y);
		y++;
	}
}
