/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:42:22 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 19:45:32 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_int(char *str)
{
	long long int	safety_ret_val;
	long long int	i;
	long long int	pos;

	pos = 1;
	i = 0;
	safety_ret_val = 0;
	while (str[i] == ' ')
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

int	handle_colors(char **line, t_map *map_info)
{
	int	col[4];

	col[3] = 2;
	col[0] = is_valid_int(&line[0][col[3]]);
	while (ft_isdigit(line[0][col[3]]) && line[0][col[3] + 1] != '\0')
		col[3]++;
	col[1] = is_valid_int(&line[0][++col[3]]);
	while (ft_isdigit(line[0][col[3]]) && line[0][col[3] + 1] != '\0')
		col[3]++;
	col[2] = is_valid_int(&line[0][++col[3]]);
	if ((!ft_strncmp(&line[0][0], "F ", 2) && map_info->color_floor != 0)
		|| (!ft_strncmp(&line[0][0], "C ", 2) && map_info->color_ceiling != 0)
		|| (col[0] > 255) || (col[1] > 255) || (col[2] > 255)
		|| (col[0] < 0) || col[1] < 0 || col[2] < 0)
		return (-1);
	if (!ft_strncmp(&line[0][0], "F ", 2))
		map_info->color_floor = 0 << 24 | col[0] << 16 | col[1] << 8 | col[2];
	if (!ft_strncmp(&line[0][0], "C ", 2))
		map_info->color_ceiling = 0 << 24 | col[0] << 16 | col[1] << 8 | col[2];
	return (0);
}
