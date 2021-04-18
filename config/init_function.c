/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:07:33 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/18 18:47:49 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_player *player)
{
	player->posX = 0;
	player->posY = 0;
	player->dirX = 1;
	player->dirY = 1;
	player->position_initialised = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	player->time = 0;
	player->old_time = 0;
	player->hit = 0;
	player->mapX = 0;
	player->mapY = 0;
	player->moveX = 0;
	player->moveY = 0;
	player->rot_left = 0;
	player->rot_right = 0;
	player->texNum = 0;
	player->texX = 0;
	player->wallX = 0;
	player->current_image.img = NULL;
}

void	init_map(t_map *map_info)
{
	map_info->window_height = 0;
	map_info->window_width = 0;
	map_info->color_floor = 0;
	map_info->color_ceiling = 0;
	map_info->te_s_color = 0;
	map_info->te_no.img = NULL;
	map_info->te_so.img = NULL;
	map_info->te_we.img = NULL;
	map_info->te_ea.img = NULL;
	map_info->te_s_color = 0;
	map_info->te_s.img = NULL;
	map_info->plan_height = 0;
	map_info->plan_width = 0;
	map_info->plan = NULL;
	map_info->sprites = NULL;
}

void	init_config(t_config *config)
{
	config->conf_file = NULL;
	config->prog_name = NULL;
	config->conf_check = 0;	
}

int		handle_resolution(char *line, t_map *map_info, t_game *game)
{
	int i;

	i = 0;
	while (!ft_isdigit(line[i]) && line[i] != '-' && line[i])
		i++;
	map_info->window_width = ft_atoi(&(line[i]));
	if (map_info->window_width <= 0)
	{
		return (exit_error(game, "Negative windows width"));
	}
	if (map_info->window_width > game->map_info.window_max_width)
		map_info->window_width = game->map_info.window_max_width;
	while (line[i] != ' ')
		i++;
	map_info->window_height = ft_atoi(&line[i]);
	if (map_info->window_height <= 0)
	{
		return (exit_error(game, "Negative windows height"));
	}
	if (map_info->window_height > game->map_info.window_max_height)
		map_info->window_height = game->map_info.window_max_height;
	return (0);
}
