/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 19:34:10 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_init_pos(t_game *game, int x, int y, char c)
{
	game->player.posx = x + 0.5;
	game->player.posy = y + 0.5;
	if (game->player.position_initialised != 0)
		exit_error(game, "Position initialised two times.");
	game->player.position_initialised = 1;
	if (c == 'N')
	{
		set_position(game, -1, 0);
		set_plane(game, 0, 0.66);
	}
	if (c == 'S')
	{
		set_position(game, 0, 1);
		set_plane(game, -0.66, 0);
	}
	if (c == 'W')
	{
		set_position(game, -1, 0);
		set_plane(game, 0, -0.66);
	}
	if (c == 'E')
	{
		set_position(game, 1, 0);
		set_plane(game, 0, 0.66);
	}
}

void	check_user_position(t_game *game, char *str, int y)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			set_init_pos(game, i, y, str[i]);
		i++;
	}
}

int	save_sprite(int x, int y, t_game *game)
{
	t_sprite	*sprite;

	if (game->map_info.sprites == NULL)
	{
		game->map_info.sprites = (t_sprite *)malloc(sizeof(t_sprite));
		if (!(game->map_info.sprites))
			return (-1);
		sprite = game->map_info.sprites;
	}
	else
	{
		sprite = game->map_info.sprites;
		while (sprite->next != NULL)
			sprite = sprite->next;
		sprite->next = (t_sprite *)malloc(sizeof(t_sprite));
		if (!(sprite->next))
			return (-1);
		sprite = sprite->next;
	}
	sprite->next = NULL;
	sprite->posx = x;
	sprite->posy = y;
	sprite->distance = 0;
	sprite->tex = &(game->map_info.te_s);
	return (0);
}

int	parse_map_line_2(t_game *game, t_map *map, char *line, int i)
{
	t_str	*map_list;

	map_list = map->plan;
	while (map_list->next != NULL)
	{
		map_list = map_list->next;
		i++;
	}
	map_list->next = (t_str *)malloc(sizeof(t_str));
	map_list->next->line = (char *)malloc(ft_strlen(line) + 1);
	if (!(map_list->next) || !(map_list->next->line))
		return (-1);
	map_list = map_list->next;
	map_list->next = NULL;
	ft_strlcpy(map_list->line, line, (ft_strlen(line) + 1));
	sprites_scanner(game, map_list->line, i);
	return (0);
}

int	parse_map_line(t_game *game, t_map *map, char *line)
{
	t_str	*map_list;
	int		i;

	i = 0;
	if (map->plan == NULL)
	{
		map->plan = (t_str *)malloc(sizeof(t_str));
		map->plan->line = (char *)malloc(ft_strlen(line) + 1);
		if (!(map->plan) || !(map->plan->line))
			return (-1);
		map->plan->next = NULL;
		ft_strlcpy(map->plan->line, line, ft_strlen(line) + 1);
		sprites_scanner(game, map->plan->line, i);
		return (0);
	}
	return (parse_map_line_2(game, map, line, i));
}
