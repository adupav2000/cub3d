/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:09:06 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/19 13:47:55 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_max_line_length(t_str *str)
{
	int	max;

	max = 0;
	while (str)
	{
		if (ft_strlen(str->line) > max)
			max = ft_strlen(str->line);
		str = str->next;
	}
	return (max);
}

int	check_map_column(t_str *str, int max_len)
{
	int		i;
	char	prev;
	char	current;
	t_str	*origine;

	i = 0;
	while (i < max_len)
	{
		str = origine;
		prev = -1;
		while (str->next != NULL)
		{
			current = -1;
			if (ft_strlen(str->line) > i)
				current = str->line[i];
			if ((prev == -1 && current == '0') || (prev == '0' && current == -1)
				|| (prev == '2' && current == -1)
				|| (prev == -1 && current == '2'))
				return (-1);
			prev = current;
			str = str->next;
		}
		i++;
	}
	return (0);
}

int	check_map_line(t_str *str)
{
	int		i;
	char	prev;

	prev = 0;
	while (str != NULL)
	{
		i = 1;
		prev = str->line[0];
		while (str->line[i - 1])
		{
			if ((prev == '\0' && str->line[i] == '0')
				|| (prev == '0' && str->line[i] == '\0')
				|| (prev == '2' && str->line[i] == '\0')
				|| (prev == '\0' && str->line[i] == '2'))
				return (-1);
			prev = str->line[i];
			i++;
		}
		str = str->next;
	}
	return (0);
}

int	check_map(t_map *map_info)
{
	t_str	*line;

	line = map_info->plan;
	return (check_map_column(line, get_max_line_length(line))
		&& check_map_line(line));
}

int	everything_was_set(t_map *map_info, t_game *game)
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
	if (game->player.position_initialised == 0)
		return (-1);
	if (check_map(map_info))
		return (-1);
	return (0);
}
