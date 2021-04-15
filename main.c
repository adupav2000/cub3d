/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:02:45 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/14 12:07:13 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game        game;

    if ((game.mlx.mlx_ptr = mlx_init()) == NULL)
        return (exit_error(&game, " mlx init didn't worked."));
    if (parsing(&game, argc, argv))
        return (exit_error(&game, " parsing failed"));
printf("Helllo\n");
    if ((game.mlx.mlx_win = mlx_new_window(game.mlx.mlx_ptr, 
        game.map_info.window_width, game.map_info.window_height,
        argv[0])) == NULL)
        return (exit_error(&game, "Error loading new window"));
    mlx_hook(game.mlx.mlx_win, 2, (1L<<0), &key_press, &game);
    mlx_hook(game.mlx.mlx_win, 3, (1L<<1), &key_release, &game);
    mlx_hook(game.mlx.mlx_win, 5, (1L<<5), &exit_success, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, raycasting, &game);
    if (game.config.screenshot && !raycasting(&game))
        if (write_and_save_screen(&game))
            return (exit_error(&game, " Screen shot couldn't be saved"));
    if (game.config.screenshot)
		return(exit_success(&game));
    mlx_loop(game.mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
