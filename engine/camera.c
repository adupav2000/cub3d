/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:09:50 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/20 16:15:50 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void move_forward(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posx +
    play->dirx * play->movex), (int)play->posy);
  if (play->movex > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posx += play->dirx * play->movex * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posx, 
    (int)(play->posy + play->diry * play->movex));
  if ((map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posy += play->diry * play->movex * 0.06;
  }
}

void move_backward(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posx +
    play->dirx * play->movex), (int)play->posy);
  if (play->movex < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posx += play->dirx * play->movex * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posx, 
    (int)(play->posy + play->diry * play->movex));
  if ((map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posy += play->diry * play->movex * 0.06;
  }
}

void move_left(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posx +
    play->planex * play->movex), (int)play->posy);
  if (play->movey > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posx += play->planex * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posx),
    (int)(play->posy + play->planex * play->movex));
  if (play->movey > 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posy += play->planey * 0.06;
  }
}

void move_right(t_game *game, t_player *play)
{
  int map_ret_val;
  
  map_ret_val = ft_map(game->map_info.plan, (int)(play->posx -
    play->planex * play->movex), (int)play->posy);
  if (play->movey < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posy -= play->planey * 0.06;
  }
  map_ret_val = ft_map(game->map_info.plan, (int)play->posx,
    (int)(play->posy - play->planex * play->movex));
  if (play->movey < 0 && (map_ret_val != -1 || map_ret_val != '1' 
    || map_ret_val != '3'))
  {
    play->posy -= play->planey * 0.06;
  }
 
}

void update_pos_view(t_game *game)
{
  t_player *play;

  play = &(game->player);
  if (play->movex > 0)
    move_forward(game, play);
  if (play->movex < 0)
    move_backward(game, play);
  if (play->movey < 0)
    move_right(game, play);
  if (play->movey > 0)
    move_left(game, play);
}

void update_rotation(t_game *game)
{
  t_player  *play;
  double    rotspeed;
  double    olddirx;
  double    oldplanex;

  play = &(game->player);
  rotspeed = 0.03;
  if (play->rot_right == 1)
  {
    olddirx = play->dirx;
    play->dirx = play->dirx * cos(-rotspeed) - play->diry 
      * sin(-rotspeed);
    play->diry = olddirx * sin(-rotspeed) + play->diry 
      * cos(-rotspeed);
    oldplanex = play->planex;
    play->planex = play->planex * cos(-rotspeed) - play->planey * sin(-rotspeed);
    play->planey = oldplanex * sin(-rotspeed) + play->planey * cos(-rotspeed);
  }
  else if (play->rot_left == 1)
  {
    olddirx = play->dirx;
    play->dirx = play->dirx * cos(rotspeed) - play->diry * sin(rotspeed);
    play->diry = olddirx * sin(rotspeed) + play->diry * cos(rotspeed);
    oldplanex = play->planex;
    play->planex = play->planex * cos(rotspeed) - play->planey * sin(rotspeed);
    play->planey = oldplanex * sin(rotspeed) + play->planey * cos(rotspeed);
  }
}
