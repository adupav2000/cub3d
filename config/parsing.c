/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:03 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/14 12:06:17 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h" 

int args_check(int argc, char **argv, t_game *game)
{
    if (argc < 2)
        return (exit_error(game, "too few arguments."));
    if (argc > 2 && ft_strncmp(argv[2], "--save", 7) == 0)
        game->config.screenshot = 1;
    if (!(game->config.prog_name = (char *)malloc(ft_strlen(argv[0]) + 1))
        || !(game->config.conf_file = (char *)malloc(ft_strlen(argv[1]) + 1)))
    {
        return (exit_error(game,
            "Malloc of the prog_name and conf_file name did not work."));
    }
    ft_strlcpy(game->config.prog_name, argv[0], (ft_strlen(argv[0]) + 1));
    ft_strlcpy(game->config.conf_file, argv[1], (ft_strlen(argv[1]) + 1));
    return (0);
}

int parse_line(char *line, t_data *data, t_map *map_info, t_game *game)
{
    if (!line[0])
        return (0);
    if ((!ft_strncmp(line, "  ", 2) || !ft_strncmp(line, "1", 1))
            && !everything_was_set(map_info, game))
        return (parse_map_line(game, map_info, line));
    else if (!ft_strncmp(line, "R ", 2)) 
        return (handle_resolution(line, map_info, game));
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
    mlx_get_screen_size(game->mlx.mlx_ptr, &game->map_info.window_max_width,
        &game->map_info.window_max_height);
	init_map(&game->map_info);
    init_player(&game->player);
    error_check = args_check(argc, argv, game);
    line = NULL;
    if (ft_strncmp(ft_split(game->config.conf_file, '.')[1], "cub", 2))
        return (exit_error(game, "uncorrect file."));
    file_desc = open(game->config.conf_file, O_RDONLY);
    while (!error_check && get_next_line(file_desc, &line))
        error_check = parse_line(line, &game->mlx, &game->map_info, game);
    error_check = everything_was_set(&game->map_info, game);
    free(line);
    close(file_desc);
    return (error_check);
}
