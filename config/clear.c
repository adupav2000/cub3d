/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:37:58 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/02 14:16:07 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    clear_player(t_player *player)
{
	
}

void    clear_mlx(t_data *mlx)
{

}
void    clear_map_info(t_map *map_info)
{

}

void    clear_config(t_config *config)
{

}

void clear_all_variables(t_game *game)
{
    clear_player(&(game->player));
    clear_mlx(&(game->mlx));
    clear_map_info(&(game->map_info));
    clear_config(&(game->config));
}

int exit_error(t_game *game)
{
    clear_all_variables(game);
    perror("Error :");
    return (-1);
}

int exit_success(t_game *game)
{
    clear_all_variables(game);
    exit(EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}