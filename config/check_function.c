/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:09:06 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/14 11:08:11 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*this function checks if all the arguments that should be recieed before the 
 * map are saved and parsed*/
int everything_was_set(t_map *map_info, t_game *game)
{
    if (map_info->window_height == 0)
        return (-1);
    if (map_info->window_width == 0)
        return (-1);
    if (map_info->color_floor == 0)
        return (-1);
    if (map_info->color_ceiling == 0)
        return (-1);
    if (map_info->te_no.img == NULL)
        return (-1);
    if (map_info->te_so.img == NULL)
        return (-1);
    if (map_info->te_we.img == NULL)
        return (-1);
    if (map_info->te_ea.img == NULL)
        return (-1);
    if (map_info->te_s.img == NULL)
        return (-1);
    // MAP CHECK MISSING
    return (0);
}
