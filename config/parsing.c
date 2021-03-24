/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:03 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/24 20:44:12 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h" 

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

int parsing(t_game *game, char **args)
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

