/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:02:45 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/26 16:03:32 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int main(int argc, char **argv)
{
    t_game        game;

    if ((game.mlx.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if (parsing(&game, argc, argv))
        return (-1);
    if ((game.mlx.mlx_win = mlx_new_window(game.mlx.mlx_ptr, 
        game.map_info.window_width, game.map_info.window_height,
        argv[0])) == NULL)
        return (EXIT_FAILURE);
    mlx_hook(game.mlx.mlx_win, KEYPRESSMASK, 0, &key_press, &game);
    mlx_hook(game.mlx.mlx_win, KEYRELEASEMASK, 0, &key_release, &game);
    mlx_hook(game.mlx.mlx_win, X_EVENT_EXIT, 0, &exit_success, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, raycasting, &game);
    mlx_loop(game.mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
