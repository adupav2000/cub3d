/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:42:27 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/15 17:52:50 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_player(t_game *game)
{
	t_player *play;

	play = &(game->player);
	if (play->current_image.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, play->current_image.img);
}

void	clear_mlx(t_data *mlx)
{
	if (mlx->mlx_ptr != NULL && mlx->mlx_win != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
}

void	clear_map_info(t_game *game)
{
	t_map	*map;
	t_str	*str;

	map = &(game->map_info);
	if (map->te_no.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, map->te_no.img);
	if (map->te_so.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, map->te_so.img);
	if (map->te_we.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, map->te_we.img);
	if (map->te_ea.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, map->te_ea.img);
	if (map->te_s.img != NULL)
		mlx_destroy_image(game->mlx.mlx_ptr, map->te_s.img);
	while (map->plan != NULL
			&& (str = (map->plan->next)) != NULL)
	{
		if (map->plan->line != NULL)
			free(map->plan->line);
		free(map->plan);
		map->plan = str;
	}
}

void	clear_config(t_config *config)
{
	int 	i;

	i = 0;
 	if (config->prog_name != NULL)
		free(config->prog_name);
	if (config->conf_file)
		free(config->conf_file);
	if (config->conf_check != NULL)
		free(config->conf_check);
}

void	clear_all_variables(t_game *game)
{
	clear_player(game);
	clear_map_info(game);
	clear_config(&(game->config));
	clear_mlx(&(game->mlx));
}