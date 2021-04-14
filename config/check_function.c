/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:09:06 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/14 20:16:39 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_map_column(t_str *str, int max_len)
{
    int     i;
    char    prev;
    t_str   *origine;

    i = 0;
    while (i < max_len)
    {
        str = origine;
        while (str->next != NULL)
        {
            prev = str->line[i];
            str = str->next;
            if ((prev == ' ' && str->line[i] == '0')
                || (prev == '0' && str->line[i] == ' ')
                || (prev == '3' && str->line[i] == ' ')
                || (prev == ' ' && str->line[i] == '3'))
                return (-1);
        }
        i++;
    }
    return (0);
}
int check_map_line(t_str *str)
{
    int     i;
    char    prev;

    while (str != NULL && str->line[0] != NULL)
    {
        i = 1;
        while (str->line[i])
        {
            prev = str->line[i - 1];
            if ((prev == ' ' && str->line[i] == '0')
                || (prev == '0' && str->line[i] == ' ')
                || (prev == '3' && str->line[i] == ' ')
                || (prev == ' ' && str->line[i] == '3'))
                return (-1);
            i++;
        }
    }
    return (0);
}

int check_map(t_map *map_info)
{
    t_str *line;

    line = map_info->plan;
    return (check_map_column(str, map_info->plan_width) && check_map_line(str));
}
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
    if (check_map(map_info))
        return (-1);
    return (0);
}
