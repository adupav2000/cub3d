/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 18:56:30 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/19 19:07:39 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_game *game, t_player *play)
{
	int	map_ret_val;

	map_ret_val = ft_map(game->map_info.plan,
			(int)(play->posx + play->dirx * play->movex), (int)play->posy);
	if (play->movex > 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posx += play->dirx * play->movex * 0.06;
	map_ret_val = ft_map(game->map_info.plan, (int)play->posx,
			(int)(play->posy + play->diry * play->movex));
	if ((map_ret_val != -1 || map_ret_val != '1' || map_ret_val != '2'))
		play->posy += play->diry * play->movex * 0.06;
}

void	move_backward(t_game *game, t_player *play)
{
	int	map_ret_val;

	map_ret_val = ft_map(game->map_info.plan,
			(int)(play->posx + play->dirx * play->movex), (int)play->posy);
	if (play->movex < 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posx += play->dirx * play->movex * 0.06;
	map_ret_val = ft_map(game->map_info.plan, (int)play->posx,
			(int)(play->posy + play->diry * play->movex));
	if ((map_ret_val != -1 || map_ret_val != '1' || map_ret_val != '2'))
		play->posy += play->diry * play->movex * 0.06;
}

void	move_left(t_game *game, t_player *play)
{
	int	map_ret_val;

	map_ret_val = ft_map(game->map_info.plan,
			(int)(play->posx + play->planex * play->movex), (int)play->posy);
	if (play->movey > 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posx += play->planex * 0.06;
	map_ret_val = ft_map(game->map_info.plan, (int)(play->posx),
			(int)(play->posy + play->planex * play->movex));
	if (play->movey > 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posy += play->planey * 0.06;
}

void	move_right(t_game *game, t_player *play)
{
	int	map_ret_val;

	map_ret_val = ft_map(game->map_info.plan,
			(int)(play->posx - play->planex * play->movex), (int)play->posy);
	if (play->movey < 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posy -= play->planey * 0.06;
	map_ret_val = ft_map(game->map_info.plan, (int)play->posx,
			(int)(play->posy - play->planex * play->movex));
	if (play->movey < 0 && (map_ret_val != -1
			|| map_ret_val != '1' || map_ret_val != '2'))
		play->posy -= play->planey * 0.06;
}

void	update_pos_view(t_game *game)
{
	t_player	*play;

	play = &(game->player);
	if (play->movex > 0)
		move_forward(game, play);
	if (play->movex < 0)
		move_backward(game, play);
	if (play->movey < 0)
		move_right(game, play);
	if (play->movey > 0)
		move_left(game, play);
}
