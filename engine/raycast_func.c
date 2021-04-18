/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:13:36 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/16 19:14:32 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void define_deltaDist(t_game *game)
{
	t_player *play;

	play = &(game->player);
	play->raydirx = play->dirx + play->planex * play->camerax;
	play->raydiry = play->diry + play->planey * play->camerax;
	play->mapx = (int)play->posx;
	play->mapy = (int)play->posy;
	play->sidedistx = 0;
	play->sidedisty = 0;
	play->deltadistx = (play->raydiry == 0) ? 0 : ((play->raydirx == 0) ? 1 : fabs(1. / play->raydirx));
	play->deltadisty = (play->raydirx == 0) ? 0 : ((play->raydiry == 0) ? 1 : fabs(1. / play->raydiry));
}

void define_side_dist(t_game *game)
{
	t_player *play;

	play = &(game->player);
	/*Making shure a wall was indeed hit*/
	play->hit = 0;
	/* making sure the side is not the one previously set*/
	play->side = -1;
	play = (&game->player);
	if (play->raydirx < 0)
	{
		play->stepx = -1;
		play->sidedistx = (play->posx - play->mapx) * play->deltadistx;
	}
	else
	{
		play->stepx = 1;
		play->sidedistx = (play->mapx + 1.0 - play->posx) * play->deltadistx;
	}
	if (play->raydiry < 0)
	{
		play->stepy = -1;
		play->sidedisty = (play->posy - play->mapy) * play->deltadisty;
	}
	else
	{
		play->stepy = 1;
		play->sidedisty = (play->mapy + 1.0 - play->posy) * play->deltadisty;
	}
}

/*
 * for the moment it performs dda, this is all what we know
 * calculate the distance to the next wall 
 * searches a wall and where it will be hit (x or y side)
 * */
void search_wall(t_game *game)
{
	t_player *play;

	play = &(game->player);
	while (play->hit == 0 &&
		   ft_map(game->map_info.plan, play->mapx, play->mapy) != -1 && play->mapx > 0 && play->mapy > 0)
	{
		if (play->sidedistx < play->sidedisty)
		{
			play->sidedistx += play->deltadistx;
			play->mapx += play->stepx;
			play->side = (play->stepx == -1) ? 0 : 1;
		}
		else
		{
			play->sidedisty += play->deltadisty;
			play->mapy += play->stepy;
			play->side = (play->stepy == -1) ? 2 : 3;
		}
		if (ft_map(game->map_info.plan, play->mapx, play->mapy) == '1' && play->side != -1)
			play->hit = 1;
	}
}

void get_line_length(t_game *game)
{
	t_player *play;

	play = &(game->player);
	if (play->side == 0 || play->side == 1)
	{
		play->perpwalldist = (play->mapx - play->posx + (1 - play->stepx) / 2) / play->raydirx;
	}
	else
	{
		play->perpwalldist = (play->mapy - play->posy + (1 - play->stepy) / 2) / play->raydiry;
	}
	play->lineheight = (int)(game->map_info.window_height / play->perpwalldist);
	play->drawstart = -play->lineheight / 2 + game->map_info.window_height / 2;
	if (play->drawstart < 0)
		play->drawstart = 0;
	play->drawend = play->lineheight / 2 + game->map_info.window_height / 2;
	if (play->drawend >= game->map_info.window_height)
		play->drawend = game->map_info.window_height - 1;
	play->wallcolor = game->map_info.color_floor;
	if (play->side == 2 || play->side == 3)
		play->wallcolor = (play->wallcolor / 2);
}
