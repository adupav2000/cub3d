/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/23 15:11:53 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int parse_map_line(t_map *map, char *line)
{
    int i;
    t_str *map_list;
 
    if (map->plan == NULL)
    {
        if (!(map->plan = (t_str *)malloc(sizeof(t_str))) || 
            !(map->plan->line = (char *)malloc(ft_strlen(line) + 1)))
            return (-1);
        map->plan->next = NULL;
        ft_strlcpy(map->plan->line, line, ft_strlen(line) + 1);
        return (0);
    }
    map_list = map->plan;
    while (map_list->next != NULL)
        map_list = map_list->next;
    if (!(map_list->next = (t_str *)malloc(sizeof(t_str))) || 
        !(map_list->next->line = (char *)malloc(ft_strlen(line) + 1)))
        return (-1);
    map_list = map_list->next;
    map_list->next = NULL;
    ft_strlcpy(map_list->line, line, (ft_strlen(line) + 1));
    return (0);
}
