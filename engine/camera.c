/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:09:50 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/08 09:30:10 by adu-pavi         ###   ########.fr       */
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
    play->posX += play->dirX * play->moveX * 0.02;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posX, 
    (int)(play->posY + play->dirY * play->moveX));
  if (play->moveX < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '2'))
  {
    play->posX += play->dirX * play->moveX * 0.02;
  }
}

void update_rotation(t_game *game)
{
  t_player  *play;
  double    rotSpeed;
  double    oldDirX;
  double    oldPlaneX;

  play = &(game->player);
  rotSpeed = 0.03;
  if (play->rot_right == 1)
  {
    oldDirX = play->dirX;
    play->dirX = play->dirX * cos(-rotSpeed) - play->dirY 
      * sin(-rotSpeed);
    play->dirY = oldDirX * sin(-rotSpeed) + play->dirY 
      * cos(-rotSpeed);
    oldPlaneX = play->planeX;
    play->planeX = play->planeX * cos(-rotSpeed) - play->planeY * sin(-rotSpeed);
    play->planeY = oldPlaneX * sin(-rotSpeed) + play->planeY * cos(-rotSpeed);
  }
  else if (play->rot_left == 1)
  {
    oldDirX = play->dirX;
    play->dirX = play->dirX * cos(rotSpeed) - play->dirY * sin(rotSpeed);
    play->dirY = oldDirX * sin(rotSpeed) + play->dirY * cos(rotSpeed);
    oldPlaneX = play->planeX;
    play->planeX = play->planeX * cos(rotSpeed) - play->planeY * sin(rotSpeed);
    play->planeY = oldPlaneX * sin(rotSpeed) + play->planeY * cos(rotSpeed);
  }
}