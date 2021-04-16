/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:32:13 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/14 13:41:44 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int sprite_bubble_sort(t_game *game)
{
    int unsorted;
    t_sprite *sprite_tmp;
    t_sprite *sprite_prev;
    t_sprite *sprite_origin;

    unsorted = 1;
    while (unsorted != 0)
    {
        unsorted = 0; 
        sprite_origin = game->map_info.sprites;
        if (sprite_origin->distance < sprite_origin->next->distance)
        {
            game->map_info.sprites = game->map_info.sprites->next;
            sprite_origin->next = game->map_info.sprites->next;
            game->map_info.sprites->next = sprite_origin;
            sprite_prev = game->map_info.sprites; 
        }
        else
        {
            sprite_origin = game->map_info.sprites->next;  
            sprite_prev = game->map_info.sprites ;
        }
        while (sprite_origin != NULL && sprite_origin->next != NULL)
        {
            // print_all_sprite(game);
            if (sprite_origin->distance >= sprite_origin->next->distance)
            {
                sprite_prev = sprite_origin;
                sprite_origin = sprite_origin->next;
            }
            else
            {
                unsorted = 1;
                sprite_prev->next = sprite_origin->next;
                sprite_origin->next = sprite_origin->next->next;
                sprite_prev->next->next = sprite_origin;
                sprite_prev = sprite_origin;
                sprite_origin = sprite_origin->next;
            }
        }

    }
    return (0);
}

double get_ss_distance(double posX, double posY, int posSX, int posSY)
{
    return ((posX - posSX) * (posX - posSX) 
        + (posY - posSY) * (posY - posSY));
}

int set_sprite_distance(t_game *game)
{
    t_sprite *sprite;

    sprite = game->map_info.sprites;
    while (sprite != NULL)    
    {
        sprite->distance = get_ss_distance(game->player.posX, 
            game->player.posY, sprite->posX, sprite->posY);
        sprite = sprite->next;
    }
    return (sprite_bubble_sort(game));
}

