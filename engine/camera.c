/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:09:50 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/03/18 21:19:38 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void update_pos_view(t_game *game)
{
  t_player *play;
  int map_ret_val;

  play = &(game->player);
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX +
    play->dirX * play->moveX), (int)play->posX);
  if (play->moveX > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '2'))
  {
    printf("moved in X direction\n");
    play->posX += play->dirX * play->moveX * 0.2;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posX, 
    (int)(play->posY + play->dirY * play->moveX));
  if (play->moveX < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '2'))
  {
    printf("moved in X direction\n");
    play->posX += play->dirX * play->moveX * 0.2;
  }
}