/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:13:36 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 14:27:50 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void define_deltaDist(t_game *game)
{
    t_player *play;

    play = &(game->player);
    play->rayDirX = play->dirX + play->planeX * play->cameraX;
    play->rayDirY = play->dirY + play->planeY * play->cameraX;
    play->mapX = (int)play->posX;
    play->mapY = (int)play->posY;
    play->sideDistX = 0;
    play->sideDistY = 0; 
    play->deltaDistX = (play->rayDirY == 0) ?
        0 : ((play->rayDirX == 0) ? 1 : fabs(1. / play->rayDirX));
    play->deltaDistY = (play->rayDirX == 0) ?
        0 : ((play->rayDirY == 0) ? 1 : fabs(1. / play->rayDirY));
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
    if (play->rayDirX < 0)
    {
        play->stepX = -1;
        play->sideDistX = (play->posX - play->mapX) * play->deltaDistX;
    }
    else
    {
        play->stepX = 1;
        play->sideDistX = (play->mapX + 1.0 - play->posX) * play->deltaDistX;
    }
    if (play->rayDirY < 0)
    {
        play->stepY = -1;
        play->sideDistY = (play->posY - play->mapY) * play->deltaDistY;
    }
    else
    {
        play->stepY = 1;
        play->sideDistY = (play->mapY + 1.0 - play->posY) * play->deltaDistY;
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
        ft_map(game->map_info.plan, play->mapX, play->mapY) != -1
        && play->mapX > 0 && play->mapY > 0)
    {
        if (play->sideDistX < play->sideDistY) 
        {
            play->sideDistX += play->deltaDistX;
            play->mapX += play->stepX;
            play->side = (play->stepX == -1) ? 0 : 1;
        }
        else
        {
            play->sideDistY += play->deltaDistY;
            play->mapY += play->stepY;
            play->side = (play->stepY == -1) ? 2 : 3;
        }
        if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '1'
                && play->side != -1)
            play->hit = 1;
    }
}

void get_line_length(t_game *game)
{
    t_player *play;

    play = &(game->player);
    if (play->side == 0 || play->side == 1)
    {
        play->perpWallDist = (play->mapX - play->posX + (1 - play->stepX) / 2)
            / play->rayDirX;
    }
    else
    {
        play->perpWallDist = (play->mapY - play->posY + (1 - play->stepY) / 2)
            / play->rayDirY;
    }
    play->lineHeight = (int)(game->map_info.window_height / play->perpWallDist);
    play->drawStart = -play->lineHeight / 2 + game->map_info.window_height / 2; 
    if (play->drawStart < 0)
        play->drawStart = 0;
    play->drawEnd = play->lineHeight / 2 + game->map_info.window_height / 2;
    if (play->drawEnd >= game->map_info.window_height)
        play->drawEnd = game->map_info.window_height - 1;
    play->wallColor = game->map_info.color_floor;
    if (play->side == 2 || play->side == 3)
       play->wallColor = (play->wallColor / 2);
}
