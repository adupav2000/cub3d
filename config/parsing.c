/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:03 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/27 16:22:26 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h" 

void init_player(t_player *player)
{
    player->posX = 3;
    player->posY = 3;
    player->dirX = -1;
    player->dirY = 0;
    player->planeX = 0;
    player->planeY = 0.66;
    player->time = 0;
    player->old_time = 0;
    player->hit = 0;
    player->mapX = 0;
    player->mapY = 0;
}    

void init_map(t_map *map_info)
{
    map_info->window_height = 0;
    map_info->window_width = 0;
    map_info->color_floor = 0;
    map_info->color_ceiling = 0;
    map_info->te_no.img = NULL;
    map_info->te_so.img = NULL;
    map_info->te_we.img = NULL;
    map_info->te_ea.img = NULL;
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

/*this function checks if all the arguments that should be recieed before the 
 * map are saved and parsed*/
int everything_was_set(t_map *map_info)
{
    if (map_info->window_height == 0)
        return (-1);
    if (map_info->window_width == 0)
        return (-1);
    if (map_info->color_floor == 0)
        return (-1);
    if (map_info->color_ceiling == 0)
        return (-1);
    if (map_info->te_no.img == NULL)
        return (-1);
    if (map_info->te_so.img == NULL)
        return (-1);
    if (map_info->te_we.img == NULL)
        return (-1);
    if (map_info->te_ea.img == NULL)
        return (-1);
    if (map_info->te_s.img == NULL)
        return (-1);
    // MAP CHECK MISSING
    return (0);
}

int parse_line(char *line, t_data *data, t_map *map_info)
{
    if (!line[0])
        return (0);
    if ((!ft_strncmp(line, "  ", 2) || !ft_strncmp(line, "1", 1))
            && !everything_was_set(map_info)) 
        return (parse_map_line(map_info, line));
    else if (!ft_strncmp(line, "R ", 2)) 
        return (handle_resolution(line, map_info));
    else if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) 
        || !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) 
        || !ft_strncmp(line, "S ", 2))
        return (handle_textures(&line, map_info, data));
    else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
        return (handle_colors(&line, map_info));
    return (-1);
}

int parsing(t_game *game)
{
    int file_desc;
    char *line; 
    int error_check;

    init_map(&game->map_info);
    init_player(&game->player); 
    error_check = 0;
    line = NULL;
    file_desc = open("config_cub3d", O_RDONLY);
    while (get_next_line(file_desc, &line) && !error_check)
        error_check = parse_line(line, &game->mlx, &game->map_info);
    error_check = everything_was_set(&game->map_info);
    free(line);
    close(file_desc);
    return (error_check);
}

