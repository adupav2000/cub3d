/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_keycode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 17:53:12 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/05 18:48:16 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int print_key_code(int key_code, t_game *game)
{
    printf("gessed key pressed : %s, key_code was : %d\n", ft_itoa(key_code), key_code);
   return (0); 
}

int main(void)
{
    t_game game;

    if ((game.mlx.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);

    mlx_hook(game.mlx.mlx_ptr, X_KEYPRESS, 0, &print_key_code, &game);
    mlx_key_hook(game.mlx.mlx_ptr, &print_key_code, &game);
    mlx_loop(game.mlx.mlx_ptr);
    return (EXIT_SUCCESS);
}
