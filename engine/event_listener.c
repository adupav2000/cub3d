/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:43:23 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/18 21:14:33 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int key_press(int key_code, t_game *game)
{
    printf("Key press\n");
    if (key_code == KEY_W || key_code == KEY_UP)
        game->player.moveX = 1;
    else if (key_code == KEY_S || key_code == KEY_DOWN)
        game->player.moveX = -1;
    else if (key_code == KEY_Q || key_code == KEY_LEFT)
        game->player.moveX = -1;
    return (0);
}

int key_release(int key_code, t_game *game)
{
    printf("key_release\n");
    if (key_code == KEY_W || key_code == KEY_UP)
        game->player.moveX = 0;
    else if (key_code == KEY_S || key_code == KEY_DOWN)
        game->player.moveX = 0;
    else if (key_code == KEY_Q || key_code == KEY_LEFT)
        game->player.moveX = 0;
    return (0);
}
