/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/15 08:46:03 by adu-pavi         ###   ########.fr       */
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

void write_verical_stripes(t_game *game, double ZBuffer[10000])
{
    int stripe;
    t_sprite_print *sprit;
    int y;
    int d;

    sprit = &(game->sprites_p);
    stripe = 0;
    stripe = sprit->drawStartX;
    while (stripe < sprit->drawEndX)
    {
        sprit->texX = (int)(256 * (stripe - (-sprit->spriteWidth / 2 
            + sprit->spriteScreenX))
            * sprit->texWidth / sprit->spriteWidth) / 256;
        if(sprit->transformY > 0 && stripe > 0
            && stripe < game->map_info.window_width 
            && sprit->transformY < ZBuffer[0])
        {
            y = sprit->drawStartY;
            printf("y : %d, spriteDrawEnd : %d\n", y, sprit->drawEndX);
            while (y < sprit->drawEndY)
            {
                d = (y) * 256 - game->map_info.window_height * 128 
                    + sprit->spriteHeight * 128;
                sprit->texY = ((d * sprit->texHeight) / sprit->spriteHeight) / 256;
                sprite_pixel_put(game, &game->map_info.te_s, stripe, y);
                y++;
            }
        }
        stripe++;
    }
}

void set_sprite(t_game *game, double ZBuffer[10000])
{
    t_sprite *sprite;
    t_player *play;
    t_sprite_print *sprit;

    if (set_sprite_distance(game))
        exit_error(game, "failed at sorting the sprites");
    sprite = game->map_info.sprites;
    play = &(game->player);
    sprit = &(game->sprites_p);
    while (sprite != NULL)     
    {
        sprit->spriteX = sprite->posX - play->posX;
        sprit->spriteY = sprite->posY - play->posY;
        sprit->invDet = 1.0 / (play->planeX * play->dirY - play->dirX * play->planeY);
        sprit->transformX = sprit->invDet * (play->dirY * sprit->spriteX
            - play->dirX * sprit->spriteY);
        sprit->transformY = sprit->invDet * (-play->planeY * sprit->spriteX 
            + play->planeX * sprit->spriteY);
        sprit->spriteScreenX = (int)((game->map_info.window_width / 2) *
            (1 + sprit->transformX / sprit->transformY)); 
        sprit->spriteHeight = abs((int)(game->map_info.window_height 
            / sprit->transformY));
        sprit->drawStartY = -sprit->spriteHeight / 2 + game->map_info.window_height / 2;
        if(sprit->drawStartY < 0)
            sprit->drawStartY = 0;
        sprit->drawEndY = sprit->spriteHeight / 2 + game->map_info.window_height / 2;
        if(sprit->drawEndY >= game->map_info.window_height)
            sprit->drawEndY = game->map_info.window_height - 1;
        sprit->spriteWidth = abs((int)(game->map_info.window_height 
            /(sprit->transformY)));
        sprit->drawStartX = -sprit->spriteWidth / 2 + sprit->spriteScreenX;
        if(sprit->drawStartX < 0)
            sprit->drawStartX = 0;
        sprit->drawEndX = sprit->spriteWidth / 2 + sprit->spriteScreenX;
        if(sprit->drawEndX >= game->map_info.window_width)
            sprit->drawEndX =  game->map_info.window_width - 1;
        write_verical_stripes(game, ZBuffer);
        sprite = sprite->next;
    }
}


int raycasting(t_game *game)
{
    int x;
    t_player *play;
    double  ZBUFFER[10000];

    play = &(game->player);
    play->current_image.img = mlx_new_image(game->mlx.mlx_ptr,
            game->map_info.window_width, game->map_info.window_height);
    play->current_image.height = game->map_info.window_height;
    play->current_image.width = game->map_info.window_width;
    play->current_image.addr = mlx_get_data_addr(play->current_image.img,
            &play->current_image.bpp, &play->current_image.line_length,
            &play->current_image.endian);
    x = 0;
    while (x < game->map_info.window_width)
    {
        play->cameraX = (2 * x / (double)game->map_info.window_width) - 1;
        define_deltaDist(game);
        define_side_dist(game);
        search_wall(game);
        get_line_length(game);
        set_wall_color(game, x);
        if (draw_floor_and_ceiling(play->current_image, x, play->drawStart, 
                (play->drawEnd - play->drawStart), &(game->map_info)))
            return (0);
        ZBUFFER[x] = play->perpWallDist;
        x++;
    }
    set_sprite(game, (double *)(ZBUFFER));
    mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, play->current_image.img, 0, 0);
    // mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, game->map_info.te_no.img, 0, 0);
    // play->rot_left = 1;
    update_pos_view(game);
    update_rotation(game);
    return (0);
}
