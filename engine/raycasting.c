/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2020/12/23 13:35:40 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int drawVertLineFromColor(t_img *img_to_change, int x, int y_begin, int len, 
        int color)
{
    if ((x > img_to_change->width) || (x < 0) ||(y_begin < 0) 
            ||(len < 0) ||((len + y_begin) > img_to_change->height))
        return (-1);
    while (len)
    {
        my_mlx_pixel_put(img_to_change, x, (y_begin + len--), color);
    }
    return (0);
}

int raycasting(t_game *game)
{
    int x;
    t_player *play;

    play = game->player;
    play->current_image->img = mlx_new_image(game->mlx->mlx_ptr,
            game->map_info->window_width, game->map_info->window_width);
    play->current_image->addr = mlx_get_data_addr(play->current_image->img, 
            &play->current_image->bpp, &play->current_image->line_length,
            &play->current_image->endian);
    x = 0;
    while (x < game->map_info->window_width)
    {
        play->cameraX = 2 * x / (double)game->map_info->window_width - 1;         
        play->rayDirX = play->dirX + play->planeX * play->cameraX;
        play->rayDirY = play->dirY + play->planeY * play->cameraX;
        if (play->rayDirX == 0)
        {
            play->deltaDistY = 0;
            play->deltaDistX = 1;
        }
        if (play->rayDirY == 0)
        {
            play->deltaDistY = 1;
            play->deltaDistX = 0;
        }
        if (play->rayDirY != 0 && play->rayDirX != 0)
        {
            play->deltaDistX = fabs(1 / play->rayDirY); 
            play->deltaDistY = fabs(1 / play->rayDirX);
        }
        if (play->rayDirX < 0)
        {
            play->stepX = -1;
            play->sideDistX = (play->posX - play->mapX) * play->deltaDistY;
        }
        else
        {
            play->stepX = 1;
            play->sideDistX = (play->mapX + 1.0 - play->posX) * play->deltaDistX;
        }
        if (play->rayDirY < 0)
        {
            play->stepY = 1;
            play->sideDistY = (play->posY - play->mapY) * play->deltaDistY;
        }
        else
        {
            play->stepY = 1;
            play->sideDistY = (play->mapY + 1.0 - play->posY) * play->deltaDistY;
        }
        while (play->hit == 0)
        {
            if (play->sideDistX < play->sideDistY) 
            {
                play->sideDistX += play->deltaDistX;
                play->mapX += play->stepX;
                play->side = 0;
            }
            else
            {
                play->sideDistY += play->deltaDistY;
                play->mapY += play->stepY;
                play->side = 1;
            }
            if (game->map_info->plan[play->mapX][play->mapY] > '0')
                play->hit = 1;
        }
        if (play->side == 0)
            play->perpWallDist = (play->mapX - play->posX + 
                    (1 - play->stepX) / 2) / play->rayDirX;
        else
            play->perpWallDist = (play->mapY - play->posY +
                   (1 - play->stepY) / 2) / play->rayDirY;
        play->lineHeight = (int)(game->map_info->window_height / play->perpWallDist);
        play->drawStart = -play->lineHeight / 2 + game->map_info->window_height; 
        if (play->drawStart < 0)
            play->drawStart = 0;
        play->drawEnd = play->lineHeight / 2 + game->map_info->window_height / 2;
        if (play->drawEnd >= game->map_info->window_height)
            play->drawEnd = game->map_info->window_height - 1;
        play->wallColor = game->map_info->color_floor;
        if (play->side == 1)
           play->wallColor = (play->wallColor / 2);
        if (drawVertLineFromColor(play->current_image, x, play->drawStart, 
                (play->drawEnd - play->drawStart), play->wallColor))
            return (-1);
        x++;
    }
    mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, 
            play->current_image->img, 0, 0);
    return (0);
}
