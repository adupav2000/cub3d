/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:09:50 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 17:06:21 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	update_rotation(t_game *game)
{
	t_player	*play;
	double		rotspeed;
	double		olddirx;
	double		oldplanex;

	play = &(game->player);
	rotspeed = 0.03;
	if (play->rot_right == 1)
		rotspeed = -rotspeed;
	else if (play->rot_left == 1)
		rotspeed = rotspeed;
	if ((play->rot_left == 1 || play->rot_right == 1)
		&& !(play->rot_left == 1 && play->rot_right == 1))
	{
		olddirx = play->dirx;
		play->dirx = play->dirx * cos(rotspeed)
			- play->diry * sin(rotspeed);
		play->diry = olddirx * sin(rotspeed)
			+ play->diry * cos(rotspeed);
		oldplanex = play->planex;
		play->planex = play->planex * cos(rotspeed)
			- play->planey * sin(rotspeed);
		play->planey = oldplanex * sin(rotspeed)
			+ play->planey * cos(rotspeed);
	}
}
