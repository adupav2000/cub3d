#include "cub3d.h" 

int parsing(t_map *map_info, data_t *data)
{
    int file_desc;
    char **line; 
    int error_check;
    
    error_check = 0;
    line = NULL;
    file_desc = open("config_cub3d", O_RDONLY);    
    char *ptr = *line;
    while (get_next_line(file_desc, line) && !error_check)
    {
        write(1, ptr, 2);
        write(1, &"\n", 1);
        if (ft_strncmp(*line, "R ", 2) && ft_strncmp(*line, "NO ", 3) &&
                ft_strncmp(*line, "SO ", 3) && ft_strncmp(*line, "WE ", 3) &&
                ft_strncmp(*line, "EA ", 3) && ft_strncmp(*line, "S ", 2) &&
                ft_strncmp(*line, "F ", 2) && ft_strncmp(*line, "C ", 2) &&
                ft_strncmp(*line, "  ", 2) && ft_strncmp(*line, "1", 1)) 
            return (-1);
        if (!ft_strncmp(*line, "R ", 2)) 
            error_check = handle_resolution(line, map_info);
        if (!ft_strncmp(*line, "NO ", 3) || !ft_strncmp(*line, "SO ", 3) 
            || !ft_strncmp(*line, "WE ", 3) || !ft_strncmp(*line, "EA ", 3) 
            || !ft_strncmp(*line, "S ", 2))
            error_check = handle_textures(line, map_info, data);
    }
    return (error_check);
}

int    handle_resolution(char **line, t_map *map_info)
{
    int i;

    i = 0;
    while (!ft_isdigit(line[0][i]))
        i++;
    map_info->window_width = ft_atoi(&(line[0][i]));
    map_info->window_width = map_info->window_width > 9999 ? 
        9999 : map_info->window_width;
    // vérifier que l'image ne soit pas trop grande
    // il manque une fonction pour ça (trouver la taille max et l'assigner)
    while (line[0][i] != ' ')
    {
        i++;
    }
    map_info->window_height = ft_atoi(&(line[0][i]));
    map_info->window_height = map_info->window_height > 9999 ? 
        9999 : map_info->window_height;
    return (0);
}

int     handle_textures(char **line, t_map *map_info, data_t *data)
{
    if (!ft_strncmp(line[0], "NO ", 3))
         if ((map_info->te_no = mlx_xpm_file_to_image(data->mlx_ptr, &line[0][2], 
            &map_info->te_no_width, &map_info->te_no_height)) == NULL)
             return (-1);
    if (!ft_strncmp(line[0], "SO ", 3))
         if ((map_info->te_so = mlx_xpm_file_to_image(data->mlx_ptr, &line[0][2], 
            &map_info->te_so_width, &map_info->te_so_height)) == NULL)
             return (-1);
    if (!ft_strncmp(line[0], "WE ", 3))
         if ((map_info->te_we = mlx_xpm_file_to_image(data->mlx_ptr, &line[0][2], 
            &map_info->te_we_width, &map_info->te_we_height)) == NULL)
             return (-1);
    if (!ft_strncmp(line[0], "EA ", 3))
         if ((map_info->te_ea = mlx_xpm_file_to_image(data->mlx_ptr, &line[0][2], 
            &map_info->te_ea_width, &map_info->te_ea_height)) == NULL)
             return (-1);
    if (!ft_strncmp(line[0], "S ", 2))
         if ((map_info->te_s = mlx_xpm_file_to_image(data->mlx_ptr, &line[0][1], 
            &map_info->te_ea_width, &map_info->te_ea_height)) == NULL)
             return (-1);
    return (0);
}

int handle_colors(char **line, t_map *map_info)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    while (!ft_isdigit(line[0][i]))
        i++;
    while (ft_isdigit(line[0][i]))
        i++;
    r = ft_atoi(&line[0][++i]);
    while (ft_isdigit(line[0][i]))
        i++;
    g = ft_atoi(&line[0][++i]);
    while (ft_isdigit(line[0][i]))
        i++;
    b = ft_atoi(&line[0][++i]);
    if (!ft_strncmp(line[0], "F ", 2))
        map_info->color_floor = 0 << 24 | r << 16 | g << 8 | b; 
    if (!ft_strncmp(line[0], "C ", 2))
        map_info->color_ceiling = 0 << 24 | r << 16 | g << 8 | b;
    return (0);
}

int read_table(int file_desc, char **line, t_map *map_info)
{
    int i;

    i = 0;
    ft_strncpy(map_info->plan[i++], line[0], ft_strlen(line[0]));
    while (get_next_line(file_desc, line))
        ft_strncpy(map_info->plan[i++], line[0], ft_strlen(line[0]));
    return (0);
}

