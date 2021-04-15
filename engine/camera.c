/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:09:50 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/14 23:01:17 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void move_forward(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX +
    play->dirX * play->moveX), (int)play->posY);
  if (play->moveX > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posX += play->dirX * play->moveX * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posX, 
    (int)(play->posY + play->dirY * play->moveX));
  if ((map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posY += play->dirY * play->moveX * 0.06;
  }
}

void move_backward(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX +
    play->dirX * play->moveX), (int)play->posY);
  if (play->moveX < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posX += play->dirX * play->moveX * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posX, 
    (int)(play->posY + play->dirY * play->moveX));
  if ((map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posY += play->dirY * play->moveX * 0.06;
  }
}

void move_left(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX +
    play->planeX * play->moveX), (int)play->posY);
  if (play->moveY > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posX += play->planeX * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX),
    (int)(play->posY + play->planeX * play->moveX));
  if (play->moveY > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posY += play->planeY * 0.06;
  }
}

void move_right(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posX -
    play->planeX * play->moveX), (int)play->posY);
  if (play->moveY < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posY -= play->planeY * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posX,
    (int)(play->posY - play->planeX * play->moveX));
  if (play->moveY < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posY -= play->planeY * 0.06;
  }
 
}

void update_pos_view(t_game *game)
{
  t_player *play;

  play = &(game->player);
  if (play->moveX > 0)
    move_forward(game, play);
  if (play->moveX < 0)
    move_backward(game, play);
  if (play->moveY < 0)
    move_right(game, play);
  if (play->moveY > 0)
    move_left(game, play);
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
