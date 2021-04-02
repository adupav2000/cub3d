/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/02 14:57:33 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void define_deltaDist(t_game *game)
{
    t_player *play;

    play = &(game->player);
    play->rayDirX = play->dirX + play->planeX * play->cameraX;
    play->rayDirY = play->dirY + play->planeY * play->cameraX;
    //printf(">>>>>>> play->cameraX %f\n", play->cameraX);
    //printf("play->rayDirY, %f, play->dirY %d, play->planY %f, \n", play->rayDirY, play->dirY, play->planeY);
    play->deltaDistX = (play->rayDirY == 0) ?
        0 : ((play->rayDirX == 0) ? 1 : fabs(1. / play->rayDirX));
    play->deltaDistY = (play->rayDirX == 0) ?
        0 : ((play->rayDirY == 0) ? 1 : fabs(1. / play->rayDirY));
    if (play->deltaDistX < 0 || play->deltaDistX > 1000)
    {
        //  printf("deltadistX : %f\n", play->deltaDistX);
        // printf("play->rayDirX, %f, play->dirX %d, play->planX %f, play->cameraX %f\n", play->rayDirX, play->dirX, play->planeX, play->cameraX);
        //  printf("deltadistY : %f\n", play->deltaDistY);

    }
}
void define_side_dist(t_game *game)
{
    t_player *play;

    play = (&game->player);
    if (play->rayDirX < 0)
    {
        play->stepX = -1;
        play->sideDistX = (play->posX - play->mapX) * play->deltaDistX;
        // if (play->sideDistX < 0 )
        // {
        //     printf("play->posX : %f, play->mapX : %d", play->posX, play->mapX);
        //     printf("play->sideDistX : %f, play->posX %f, play->mapX : %d, play->deltaDistX : %f, play->rayDirX : %f, play->rayDirY : %f\n",play->sideDistX, play->posX, play->mapX, play->deltaDistX, play->rayDirX, play->rayDirY);
        // }
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
    if (play->sideDistY < 0 || play->sideDistX < 0)
    {
        // printf("play->sideDistY : %f\n", play->sideDistY);
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
    /*Making shure a wall was indeed hit*/
    play->hit = 0;
    /* making sure the side is not the one previously set*/
    play->side = -1;
    while (play->hit == 0 && 
            ft_map(game->map_info.plan, play->mapX, play->mapY) != -1
            && play->mapX > 0 && play->mapY > 0)
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
        //printf("ft_map : game->map_info.plan : %c\n", ft_map(game->map_info.plan, play->mapX, play->mapY));
        if (ft_map(game->map_info.plan, play->mapX, play->mapY) > '0'
                && play->side != -1)
            play->hit = 1;
    }
}

void get_line_length(t_game *game)
{
    t_player *play;

    play = &(game->player);
    if (play->side == 0)
    {
        play->perpWallDist = (play->mapX - play->posX + (1 - play->stepX) / 2)
            / play->rayDirX;
//       printf("X : play->mapX : %d, play->posX %f, play->stepX : %d,play->perWallDist %f, play->rayDirX %f\n", play->mapX, play->posX, play->stepX, play->perpWallDist, play->rayDirX); 
    }
    else
    {
        play->perpWallDist = (play->mapY - play->posY + (1 - play->stepY) / 2)
            / play->rayDirY;
 //       printf("Y : play->mapY : %d, play->posY %f, play->stepY : %d, play-perpWallDist %f, play->rayDirY %f\n", play->mapY, play->posY, play->stepY, play->perpWallDist, play->rayDirY);
    }
    play->lineHeight = (int)(game->map_info.window_height / play->perpWallDist);
    play->drawStart = -play->lineHeight / 2 + game->map_info.window_height / 2; 
    if (play->drawStart < 0)
        play->drawStart = 0;
    play->drawEnd = play->lineHeight / 2 + game->map_info.window_height / 2;
    if (play->drawEnd >= game->map_info.window_height)
        play->drawEnd = game->map_info.window_height - 1;
    play->wallColor = game->map_info.color_floor;
    if (play->side == 1)
       play->wallColor = (play->wallColor / 2);
    if (play->drawStart > play->drawEnd)
    {
  //      printf("play->drawStart : %d, play->drawEnd : %d, play->lineHeight : %dgame->map_info.windows_height %d\n", play->drawStart, play->drawEnd, play->lineHeight, game->map_info.window_height);
    }
}

int raycasting(t_game *game)
{
    //printf("\n\n");
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
    // w is the position that goes throught every vertical stripe 
    update_pos_view(game);
    update_rotation(game);
    x = 0;
    while (x < game->map_info.window_width)
    {
        play->mapX = (int)play->posX;
        play->mapY = (int)play->posY;
        play->cameraX = (2 * x / (double)game->map_info.window_width) - 1;
        define_deltaDist(game);
        printf("play->RayDirX: %f;play->RayDirY : %f", play->rayDirX, play->rayDirY);
        define_side_dist(game);
        search_wall(game);
        printf(" play->sideDistX : %f, play->sideDisY : %f",play->sideDistX, play->sideDistY);
        get_line_length(game);
        printf(" play->perpWallDist : %f\n",play->perpWallDist);
        set_wall_color(game);
        if (drawVertLineFromColor(play->current_image, x, play->drawStart, 
                (play->drawEnd - play->drawStart), play->wallColor))
            return (-1);
        if (draw_floor_and_ceiling(play->current_image, x, play->drawStart, 
                (play->drawEnd - play->drawStart), &(game->map_info)))
            return (0);
        x++;
    }
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, play->current_image.img, 0, 0);
    play->rot_left = 1;
    return (0);
}
