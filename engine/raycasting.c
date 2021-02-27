/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/27 19:12:09 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int drawVertLineFromColor(t_img img_to_change, int x, int y_begin, int len, 
        int color)
{
//    printf("x : %d, img_to_change.width %d, y_begin : %d, len %d, img_to_change.height %d", x, img_to_change.width, y_begin, len, img_to_change.height);
    if ((x > img_to_change.width) || (x < 0) ||(y_begin < 0) 
            ||(len < 0) ||((len + y_begin) > img_to_change.height))
        return (-1);
    while (len)
    {
        my_mlx_pixel_put(&img_to_change, x, (y_begin + len--), color);
    }
    return (0);
}

/*
 * functions returns the character at the given height and width
 * the map is given in a t_str linked list
 * */
char   ft_map(t_str *map, int width, int height)
{
    while (map && --height)
       map = map->next; 
    if (map && width <= ft_strlen(map->line))
        return (map->line[width]);
    printf("returned a -1 SHIT!\n");
    return (-1);
}

/*
 *for the moment it performs dda, this is all what we know
 * calculate the distance to the next wall 
 * */
void perform_dda(t_game *game)
{ 
    t_player *play;

    play = &(game->player);
    play->hit = 0;
    while (play->hit == 0 && ft_map(game->map_info.plan, play->mapX, play->mapY) != -1)
    {
        printf("play->sideDistX : %f, play->sideDistY : %f\n", play->sideDistX, play->sideDistY);
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
        if (ft_map(game->map_info.plan, play->mapX, play->mapY) > '0')
            play->hit = 1;
    }
}

void define_deltaDist(t_game *game)
{
    t_player *play;

    play = &(game->player);
    play->rayDirX = play->dirX + play->planeX * play->cameraX;
    play->rayDirY = play->dirY + play->planeY * play->cameraX;
    printf("play->rayDirX, %f\n", play->rayDirX);
    printf("play->rayDirY, %f\n", play->rayDirY);
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
        play->deltaDistX = (play->rayDirY == 0) ? 
            0 : ((play->rayDirX == 0) ? 1 : fabs(1 / play->rayDirX));
        printf("play->deltaDistX : %f\n", play->deltaDistX);
        play->deltaDistY = (play->rayDirX == 0) ? 
            0 : ((play->rayDirY == 0) ? 1 : fabs(1 / play->rayDirY));
        printf("play->deltaDistY : %f\n", play->deltaDistY);
    }
}
void define_side_dist(t_game *game)
{
    t_player *play;

    play = (&game->player);
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
}

void get_line_length(t_game *game)
{
    t_player *play;

    play = &(game->player);
    play->lineHeight = (int)(game->map_info.window_height / play->perpWallDist);
    play->drawStart = -play->lineHeight / 2 + game->map_info.window_height; 
    if (play->drawStart < 0)
        play->drawStart = 0;
    play->drawEnd = play->lineHeight / 2 + game->map_info.window_height / 2;
    if (play->drawEnd >= game->map_info.window_height)
        play->drawEnd = game->map_info.window_height - 1;
    play->wallColor = game->map_info.color_floor;
    if (play->side == 1)
       play->wallColor = (play->wallColor / 2);
}

int raycasting(t_game *game)
{
    int x;
    t_player *play;

    play = &(game->player);
    
    play->current_image.img = mlx_new_image(game->mlx.mlx_ptr,
            game->map_info.window_width, game->map_info.window_height);
    play->current_image.height = game->map_info.window_height;
    play->current_image.width = game->map_info.window_width;
    play->current_image.addr = mlx_get_data_addr(play->current_image.img,
            &play->current_image.bpp, &play->current_image.line_length,
            &play->current_image.endian);
    x = 0;
    // w is the position that goes throught every vertical stripe 
    play->mapX = (int)play->posX;
    play->mapY = (int)play->posY;
    while (x < game->map_info.window_width)
    {
        // default position of the player
        play->cameraX = (double)(2 * x) / (double)game->map_info.window_width - 1;         
        printf("window_width %d and x : %d, camX %f\n", game->map_info.window_width, x, play->cameraX);
//        printf("play->RayDirX: %f;play->RayDirY : %f\n", play->rayDirX, play->rayDirY);
        define_deltaDist(game);
        define_side_dist(game);
        perform_dda(game);
        if (play->side == 0)
            play->perpWallDist = (play->mapX - play->posX +
                    (1 - play->stepX) / 2) / play->rayDirX;
        else
            play->perpWallDist = (play->mapY - play->posY +
                   (1 - play->stepY) / 2) / play->rayDirY;
 //       printf("perpWallDist : %f\n", play->perpWallDist);
        get_line_length(game);
            //printf("play->drawStart : %d; play->drawEnd: %d;\n\n", play->drawStart, play->drawEnd);
        if (drawVertLineFromColor(play->current_image, x, play->drawStart, 
                (play->drawEnd - play->drawStart), play->wallColor))
            return (-1);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, 
            play->current_image.img, 0, 0);
    return (0);
}
