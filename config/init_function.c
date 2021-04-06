/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:07:33 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/03/23 14:08:54 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_player(t_player *player)
{
    player->posX = 5;
    player->posY = 5;
    player->dirX = 0;
    player->dirY = -1;
    player->planeX = 0;
    player->planeY = 0.66;
    player->time = 0;
    player->old_time = 0;
    player->hit = 0;
    player->mapX = 0;
    player->mapY = 0;
    player->moveX = 0;
    player->moveY = 0;
    player->rot_left = 0;
    player->rot_right = 0;
}    

void init_map(t_map *map_info)
{
    map_info->window_height = 0;
    map_info->window_width = 0;
    map_info->color_floor = 0x33C6E3;
    map_info->color_ceiling = 0xA0764C;

    map_info->te_no_color = 0xFFFFFF;
    map_info->te_so_color = 0xCCCCCC;
    map_info->te_we_color = 0xFF44FF;
    map_info->te_ea_color = 0x44FF44;
    /*write here if you know why this is for*/
    map_info->te_s_color = 0;
    map_info->te_no.img = NULL;
    map_info->te_so.img = NULL; 
    map_info->te_we.img = NULL;
    map_info->te_ea.img = NULL;
    /*write here if you know why this is for*/
    map_info->te_s_color = 0;
    map_info->te_s.img = NULL;
    map_info->plan_height = 0;
    map_info->plan_width = 0;
    map_info->plan = NULL;
}

int    handle_resolution(char *line, t_map *map_info)
{
    int i;

    i = 0;
    while (!ft_isdigit(line[i]))
        i++;
    map_info->window_width = ft_atoi(&(line[i]));
    map_info->window_width = map_info->window_width > 9999 ? 
        9999 : map_info->window_width;
    // vérifier que l'image ne soit pas trop grande
    // il manque une fonction pour ça (trouver la taille max et l'assigner)
    while (line[i] != ' ' && line[i])
    {
        i++;
    }
    map_info->window_height = ft_atoi(&line[i]);
    map_info->window_height = map_info->window_height > 9999 ? 
        9999 : map_info->window_height;
    return (0);
}