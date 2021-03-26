/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:03 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/03/25 19:22:58 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h" 

int args_check(int argc, char **argv, t_game *game)
{
    if (argc < 2)
        return (exit_error(game));
    if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
        game->config.screenshot = 1;
    if (!(game->config.prog_name = (char *)malloc(ft_strlen(argv[0]) + 1))
        || !(game->config.conf_file = (char *)malloc(ft_strlen(argv[1]) + 1)))
    {
        printf("Malloc error \n");
        return (exit_error(game));
    }
    ft_strlcpy(game->config.prog_name, argv[0], (ft_strlen(argv[0]) + 1));
    ft_strlcpy(game->config.conf_file, argv[1], (ft_strlen(argv[1]) + 1));
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

int parsing(t_game *game, int argc, char **argv)
{
    int file_desc;
    char *line; 
    int error_check;

    game->config.screenshot = 0;
    init_map(&game->map_info);
    init_player(&game->player);
    error_check = args_check(argc, argv, game);
    line = NULL;
    file_desc = open(game->config.conf_file, O_RDONLY);
    while (get_next_line(file_desc, &line) && !error_check)
        error_check = parse_line(line, &game->mlx, &game->map_info);
    error_check = everything_was_set(&game->map_info);
    free(line);
    close(file_desc);
    return (error_check);
}
