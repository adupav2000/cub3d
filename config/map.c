/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:06:56 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/14 10:53:41 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    set_init_pos(t_game *game, int x, int y, char c)
{
    if (!game->player.position_initialised)
    {
		game->player.posX = x;
        game->player.posY = y;
        game->player.position_initialised = 1;
        if (c == 'N')
            game->player.dirY = 1;
        if (c == 's')
            game->player.dirY = -1;
        if (c == 'W')
            game->player.dirX = -1;
        if (c == 'E')
            game->player.dirX = 1;
    }
    else
    {
        exit_error(game, "multiple positions registered");
    }
}

void    check_user_position(t_game *game, char *str, int y)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
            set_init_pos(game, i, y, str[i]);
        i++;
    }
}

int save_sprite(int x, int y, t_game *game)
{
    t_sprite *sprite;

    if (game->map_info.sprites == NULL)
    {
        if (!(game->map_info.sprites = (t_sprite *)malloc(sizeof(t_sprite))))
            return (-1);
        sprite = game->map_info.sprites;
    }
    else
    {
        sprite = game->map_info.sprites;
        while (sprite->next != NULL)
            sprite = sprite->next;
        if (!(sprite->next = (t_sprite *)malloc(sizeof(t_sprite))))
            return (-1);
        sprite = sprite->next;
    }
    sprite->next = NULL; 
    sprite->posX = x;
    sprite->posY = y;
    sprite->distance = 0;
    sprite->tex = &(game->map_info.te_s);
    return (0);
}

void    sprites_scanner(t_game *game, char *str, int y)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '2')
        {
            save_sprite(i, y, game);
            str[i] = '0';
        }
        i++;
    }
    check_user_position(game, str, y);
}

int parse_map_line(t_game *game, t_map *map, char *line)
{
    t_str *map_list;
    int     i;
 
    i = 0;
    if (map->plan == NULL)
    {
        if (!(map->plan = (t_str *)malloc(sizeof(t_str))) || 
            !(map->plan->line = (char *)malloc(ft_strlen(line) + 1)))
        {
            return (-1);
        }
        map->plan->next = NULL;
        ft_strlcpy(map->plan->line, line, ft_strlen(line) + 1);
        sprites_scanner(game, map->plan->line, i);
        return (0);
    }
    map_list = map->plan;
    while (map_list->next != NULL)
    {
        map_list = map_list->next;
        i++;
    }
    if (!(map_list->next = (t_str *)malloc(sizeof(t_str))) || 
        !(map_list->next->line = (char *)malloc(ft_strlen(line) + 1)))
        {
            printf("whats ?\n");
            return (-1);
        }
    map_list = map_list->next;
    map_list->next = NULL;
    ft_strlcpy(map_list->line, line, (ft_strlen(line) + 1));
    sprites_scanner(game, map_list->line, i);
    printf("whats ?\n");
    return (0);
}
