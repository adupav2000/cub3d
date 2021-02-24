/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/24 22:39:20 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int parse_map_line(t_map *map, char *line)
{
    int i;
    t_str *map_list;
    
    if (map->plan == NULL)
    {
        if (!(map->plan = malloc(sizeof(t_str))) ||
            !(map->plan->line = (char *)malloc(sizeof(ft_strlen(line)) + 1)))
            return (-1);
        ft_strlcpy(map->plan->line, line, ft_strlen(line));
        printf("first line : %s\n", map->plan->line);
        map->plan->next = NULL;
        return (0);
    }
    map_list = map->plan;
    while (map_list != NULL)
        map_list = map_list->next;
    if (!(map_list = (t_str *)malloc(sizeof(t_str))) || 
            !(map_list->line = (char *)malloc(ft_strlen(line) + 1)))
        return (-1);
    map_list->next = NULL;
    ft_strlcpy(map_list->line, line, (ft_strlen(line) + 1));
    printf("next line : %s\n", map_list->line);
    return (0);
}
