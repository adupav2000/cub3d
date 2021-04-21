/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:42:10 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 19:32:50 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_position(t_game *game, double x, double y)
{
	game->player.dirx = x;
	game->player.diry = y;
}

void	set_plane(t_game *game, double planex, double planey)
{
	game->player.planex = planex;
	game->player.planey = planey;
}

void	sprites_scanner(t_game *game, char *str, int y)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '2')
		{
			save_sprite(i, y, game);
			str[i] = '0';
		}
		i++;
	}
	check_user_position(game, str, y);
}
