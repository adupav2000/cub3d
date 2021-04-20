/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:42:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 11:54:43 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h" 

int	is_valid_int(char *str)
{
	long long int safety_ret_val;
	long long int i;
	long long int pos;

	pos = 1;
	i = 0;
	safety_ret_val = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			pos *= -1;
	while (str[i] <= '9' && str[i] >= '0')
		safety_ret_val = safety_ret_val * 10 + (str[i++] - '0');
	i = (safety_ret_val * pos);
	if (i >= 2147483647)
		return (100000);
	if (i <= -2147483648)
		return (0);
	return (i);
}

int handle_colors(char **line, t_map *map_info)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    while (!ft_isdigit(line[0][i]))
        i++;
    while (ft_isdigit(line[0][i]) && line[0][i + 1] != '\n')
        i++;
    r = is_valid_int(&line[0][++i]);
    while (ft_isdigit(line[0][i]) && line[0][i + 1] != '\n')
        i++;
    g = is_valid_int(&line[0][++i]);
    while (ft_isdigit(line[0][i]) && line[0][i + 1] != '\n')
        i++;
    b = is_valid_int(&line[0][++i]);
	if ((!ft_strncmp(&line[0][0], "F ", 2) && map_info->color_floor != 0)
		|| (!ft_strncmp(&line[0][0], "C ", 2) && map_info->color_ceiling != 0)
		|| (r > 255) || (g > 255) || (b > 255) || (r < 0) || g < 0 || b < 0)
		return (-1);
    if (!ft_strncmp(&line[0][0], "F ", 2))
        map_info->color_floor = 0 << 24 | r << 16 | g << 8 | b;
    if (!ft_strncmp(&line[0][0], "C ", 2))
        map_info->color_ceiling = 0 << 24 | r << 16 | g << 8 | b;
    return (0);
}
