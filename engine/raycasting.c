/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:32:11 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 15:31:47 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
            && sprit->transformY < ZBuffer[stripe])
        {
            y = sprit->drawStartY;
            while (y < sprit->drawEndY)
            {
                d = (y) * 256 - game->map_info.window_height * 128 
                    + sprit->spriteHeight * 128;
                sprit->texY = ((d * sprit->texHeight) / sprit->spriteHeight) / 256;
                sprite_pixel_put(game, &game->map_info.te_s, sprit, stripe, y);
                y++;
            }
        }
        stripe++;
    }
}

void set_sprite_p_and_ht(t_player *play,
	t_game *game,
	t_sprite_print *sprit,
	t_sprite *sprite)
{
        sprit->spriteX = sprite->posX - play->posX;
        sprit->spriteY = sprite->posY - play->posY;
	sprit->texWidth = game->map_info.te_s.width;
	sprit->texHeight = game->map_info.te_s.height;
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
		set_sprite_p_and_ht(play, game, sprit, sprite);
		write_verical_stripes(game, ZBuffer);
		sprite = sprite->next;
    }
}

int init_mlx_obj(t_player *play, t_game *game)
{
	play->current_image.img = mlx_new_image(game->mlx.mlx_ptr,
            game->map_info.window_width, game->map_info.window_height);
	if (play->current_image.img == NULL)
		return (-1);
	play->current_image.height = game->map_info.window_height;
	play->current_image.width = game->map_info.window_width;
	play->current_image.addr = mlx_get_data_addr(play->current_image.img,
		&play->current_image.bpp, &play->current_image.line_length,
		&play->current_image.endian);
	if (play->current_image.addr == NULL)
		return (-1);
	return (0);
}

int raycasting(t_game *game)
{
	int x;
	t_player *play;
	double  ZBUFFER[10000];

	play = &(game->player);
	if (init_mlx_obj(play, game))
		return (exit_error(game, "malloc error raycast"));
        x = 0;
	while (x < game->map_info.window_width)
	{
		play->cameraX = (2 * x / (double)game->map_info.window_width) - 1;
		define_deltaDist(&(game->player));
		define_side_dist(game);
		search_wall(game);
		get_line_length(game);
		set_wall_color(game, x);
		if (draw_floor_and_ceiling(play->current_image, x, play->drawStart, 
			(play->drawEnd - play->drawStart), &(game->map_info)))
			break;
		ZBUFFER[x++] = play->perpWallDist;
	}
	set_sprite(game, (double *)(ZBUFFER));
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.mlx_win, play->current_image.img, 0, 0);
	mlx_destroy_image(game->mlx.mlx_ptr, play->current_image.img);
	play->current_image.img = NULL;
	play->current_image.addr = NULL;
	update_pos_view(game);
	update_rotation(game);
	return (0);
}
