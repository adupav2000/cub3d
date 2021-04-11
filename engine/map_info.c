/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:30:18 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/09 21:08:37 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * functions returns the character at the given height and width
 * the map is given in a t_str linked list
 * */
char   ft_map(t_str *map, int width, int height)
{
    while (map && (--height > 0))
		map = map->next; 
    if (map && width <= (int)ft_strlen(map->line))
		return (map->line[width]);
    //printf("returned a -1 SHIT! : width ; %d, height : %d\n", width, height);
    return (-1);
}

/*THIS FUNCTION HAS TO BE CHANGED
 * FOR BETTER USE...*/
void set_wall_color(t_game *game, int x)
{
    t_player *play;
    int y;
    int   color;

    play = &(game->player);
    play->texNum = ft_map(game->map_info.plan, play->mapX, play->mapY) - 1;
    if (play->side == 0)
        play->wallX = play->posX + play->perpWallDist * play->rayDirX;
    else
        play->wallX = play->posX + play->perpWallDist * play->rayDirX;
    play->wallX -= floor(play->wallX);
    play->texX = (int)play->wallX * (double)game->map_info.te_so.width;
    if(play->side == 0 && play->rayDirX > 0)
        play->texX = game->map_info.te_so.width - play->texX - 1;
    if(play->side == 1 && play->rayDirY < 0)
        play->texX = game->map_info.te_so.width - play->texX - 1;
    play->step = 1.0 * game->map_info.te_so.height / play->lineHeight;
    play->texPos = (play->drawStart - game->map_info.window_height 
        / 2 + play->lineHeight / 2) * play->step;
    y = play->drawStart;
    while (y < play->drawEnd)
    {
        play->texY = (int)play->texPos & (game->map_info.te_so.height - 1);
        play->texPos += play->step;
        color = load_color_from_tex(&(game->map_info.te_so), play->texX, play->texY);
        my_mlx_pixel_put(&(play->current_image), x, y, color);
        y++;
    }
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '1')
        play->wallColor = game->map_info.te_no_color;
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '2')
        play->wallColor = game->map_info.te_so_color;
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '3')
        play->wallColor = game->map_info.te_ea_color;
    else
        play->wallColor = game->map_info.te_we_color;
}