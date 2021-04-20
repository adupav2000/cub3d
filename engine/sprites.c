/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:32:13 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 16:21:21 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_bubble_sort_1(t_sprite *sprite_tmp, t_sprite *sprite_prev,
						t_sprite *sprite_origin, int unsorted)
{
	while (sprite_origin != NULL && sprite_origin->next != NULL)
	{
		if (sprite_origin->distance >= sprite_origin->next->distance)
		{
			sprite_prev = sprite_origin;
			sprite_origin = sprite_origin->next;
		}
		else
		{
			unsorted = 1;
			sprite_prev->next = sprite_origin->next;
			sprite_origin->next = sprite_origin->next->next;
			sprite_prev->next->next = sprite_origin;
			sprite_prev = sprite_origin;
			sprite_origin = sprite_origin->next;
		}
	}
}

int		sprite_bubble_sort(t_game *game)
{
	int			unsorted;
	t_sprite	*sprite_tmp;
	t_sprite	*sprite_prev;
	t_sprite	*sprite_origin;

	unsorted = 1;
	while (unsorted != 0)
	{
		unsorted = 0;
		sprite_origin = game->map_info.sprites;
		if (sprite_origin->distance < sprite_origin->next->distance)
		{
			game->map_info.sprites = game->map_info.sprites->next;
			sprite_origin->next = game->map_info.sprites->next;
			game->map_info.sprites->next = sprite_origin;
			sprite_prev = game->map_info.sprites;
		}
		else
		{
			sprite_origin = game->map_info.sprites->next;
			sprite_prev = game->map_info.sprites;
		}
		sprite_bubble_sort_1(sprite_tmp, sprite_prev, sprite_origin, unsorted);
	}
	return (0);
}

double	get_ss_distance(double pos_x, double pos_y, int pos_sx, int pos_sy)
{
	return ((pos_x - pos_sx) * (pos_x - pos_sx)
		+ (pos_y - pos_sy) * (pos_y - pos_sy));
}

int		set_sprite_distance(t_game *game)
{
	t_sprite *sprite;

	sprite = game->map_info.sprites;
	while (sprite != NULL)
	{
		sprite->distance = get_ss_distance(game->player.posx,
			game->player.posy, sprite->posx, sprite->posy);
		sprite = sprite->next;
	}
	return (sprite_bubble_sort(game));
}
