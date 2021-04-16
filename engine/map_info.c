/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:30:18 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/16 16:08:03 by adu-pavi         ###   ########.fr       */
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
	{
		if (map->line[width] == ' ')
			return ('1');
		return (map->line[width]);
	}
    //printf("returned a -1 SHIT! : width ; %d, height : %d\n", width, height);
    return (-1);
}

static t_img *get_current_tex(t_game *game)
{
    t_player    *play;
    t_img       *tex;

    play = &(game->player);
    tex = &(game->map_info.te_we); 
    if (play->side == 1)
        tex = &(game->map_info.te_no); 
    else if (play->side == 2)
        tex = &(game->map_info.te_so); 
    else if (play->side == 3)
        tex = &(game->map_info.te_ea); 
    return (tex); 
}

/*THIS FUNCTION HAS TO BE CHANGED
 * FOR BETTER USE...*/
void set_wall_color(t_game *game, int x)
{
    t_player        *play;
    int             y;
    unsigned int    color;
    t_img           *tex;

    tex = get_current_tex(game);
    play = &(game->player);
    if (play->side == 0 || play->side == 1)
        play->wallX = play->posY + play->perpWallDist * play->rayDirY;
    else
        play->wallX = play->posX + play->perpWallDist * play->rayDirX;
    play->wallX -= floor(play->wallX);
    play->texX = (int)(play->wallX * (double)tex->width);
    if(play->side == 0 && play->rayDirX > 0)
        play->texX = tex->width - play->texX - 1;
    if(play->side == 1 && play->rayDirY < 0)
        play->texX = tex->width - play->texX - 1;
    play->step = 1.0 * tex->height / play->lineHeight;
    play->texPos = (play->drawStart - game->map_info.window_height 
        / 2 + play->lineHeight / 2) * play->step;
    y = play->drawStart;
    while (y < play->drawEnd)
    {
        play->texY = (int)play->texPos & (tex->height - 1);
        play->texPos += play->step;
        texture_pixel_put(game, tex, x, y);
        y++;
    }
 }