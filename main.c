/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:02:45 by AlainduPa         #+#    #+#             */
/*   Updated: 2020/12/26 16:34:56 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
    t_game        game;
    
    if ((game.mlx->mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if (parsing(game))
        return (-1);
    if ((game.mlx->mlx_win = mlx_new_window(game.mlx->mlx_ptr, game.map_info->window_width,
                  game.map_info->window_height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    mlx_loop_hook(game.mlx->mlx_ptr, raycasting, game);
    mlx_loop(game.mlx->mlx_ptr);
    return (EXIT_SUCCESS);
}
