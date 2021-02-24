/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:42:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/15 11:54:07 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h" 

int handle_colors(char **line, t_map *map_info)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    while (!ft_isdigit(line[0][i]) && line[0][i])
        i++;
    while (ft_isdigit(line[0][i]) && line[0][i])
        i++;
    r = ft_atoi(&line[0][++i]);
    while (ft_isdigit(line[0][i]) && line[0][i])
        i++;
    g = ft_atoi(&line[0][++i]);
    while (ft_isdigit(line[0][i]) && line[0][i])
        i++;
    b = ft_atoi(&line[0][++i]);
    if (!ft_strncmp(line[0], "F ", 2))
        map_info->color_floor = 0 << 24 | r << 16 | g << 8 | b; 
    if (!ft_strncmp(line[0], "C ", 2))
        map_info->color_ceiling = 0 << 24 | r << 16 | g << 8 | b;
    return (0);
}
