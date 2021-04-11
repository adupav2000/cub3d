/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:02:45 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/11 18:54:01 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
        return (exit_error(&game, "Error loading new window"));
    mlx_hook(game.mlx.mlx_win, KEYPRESSMASK, 0, &key_press, &game);
    mlx_hook(game.mlx.mlx_win, KEYRELEASEMASK, 0, &key_release, &game);
    mlx_hook(game.mlx.mlx_win, X_EVENT_EXIT, 0, &exit_success, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, raycasting, &game);
    if (game.config.screenshot && !raycasting(&game))
        if (write_and_save_screen(&game))
            return (EXIT_FAILURE);
    if (game.config.screenshot)
		return(exit_success(&game));
    mlx_loop(game.mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
