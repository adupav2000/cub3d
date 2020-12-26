/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2020/12/18 15:21:50 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int parse_map_line(t_map *map, char *line)
{
    int i;

    if (!line[0])
        return (-1);
    if (!(map->plan[map->plan_height++] = ft_strdup(line)))
        return (-1);
    return (0);
}
