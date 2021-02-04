/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/04 05:48:45 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char ft_map(t_str *map, int width, int height)
{
    t_str *map_line;

    map_line = map;
    while (map_line && height--)
       map_line = map_line->next; 
    if (map_line && width <= ft_strlen(map_line->line))
        return (map_line->line[width]);
    return (-1);
}

int parse_map_line(t_map *map, char *line)
{
    int i;
    t_str *map_list;

    if (!line[0])
        return (-1);
    if (map->plan == NULL)
    {
        if (!(map->plan = malloc(sizeof(t_str))) ||
            !(map->plan->line = (char *)malloc(sizeof(ft_strlen(line)) + 1)))
            return (-1);
        ft_strlcpy(map->plan->line, line, ft_strlen(line));
        map->plan->next = NULL;
        printf("first line : %s\n", map->plan->line);
        return (0);
    }
    map_list = map->plan;
    while (map_list)
       map_list = map_list->next;
    if (!(map_list = (t_str *)malloc(sizeof(t_str))) || 
            !(map_list->line = (char *)malloc(sizeof(ft_strlen(line)) + 1)))
        return (-1);
    map_list->next = NULL;
    ft_strlcpy(map_list->line, line, ft_strlen(line));
    printf("line : %s\n", map_list->line);
    return (0);
}
