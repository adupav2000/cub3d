/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:30:18 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/03/23 14:33:26 by adu-pavi         ###   ########.fr       */
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
    if (map && width <= ft_strlen(map->line))
		return (map->line[width]);
    //printf("returned a -1 SHIT! : width ; %d, height : %d\n", width, height);
    return (-1);
}

/*THIS FUNCTION HAS TO BE CHANGED
 * FOR BETTER USE...*/
void set_wall_color(t_game *game)
{
    t_player *play;

    play = &(game->player);
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '1')
        play->wallColor = game->map_info.te_no_color;
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '2')
        play->wallColor = game->map_info.te_so_color;
    if (ft_map(game->map_info.plan, play->mapX, play->mapY) == '3')
        play->wallColor = game->map_info.te_ea_color;
    else 
        play->wallColor = game->map_info.te_we_color;
}