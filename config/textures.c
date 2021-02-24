/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlainduPavillon <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:10 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/02/08 08:17:52 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h" 

int     handle_textures(char **line, t_map *map_info, t_data *data)
{
    int i = 0;

    i = 2;
    while (line[0][i] && line[0][i] == ' ')
        i++;
    if (!ft_strncmp(line[0], "NO ", 3))
        return (load_texture(&line[0][i], &map_info->te_no, data));
    if (!ft_strncmp(line[0], "SO ", 3))
        return (load_texture(&line[0][i], &map_info->te_so, data));
    if (!ft_strncmp(line[0], "WE ", 3))
        return (load_texture(&line[0][i], &map_info->te_we, data));
    if (!ft_strncmp(line[0], "EA ", 3))
        return (load_texture(&line[0][i], &map_info->te_ea, data));
    if (!ft_strncmp(line[0], "S ", 2))
        return (load_texture(&line[0][i], &map_info->te_s, data));
    return (-1);
}

int load_texture(char *tex_link, t_img *img, t_data *mlx)
{
    printf ("tex link : %s\n", tex_link);
    if ((img->img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex_link, 
            &img->width, &img->height)) != NULL)
    {
        printf("\nIt kind of works lol\n");
        if ((img->addr = mlx_get_data_addr(img->img, &(img->bpp), 
                    &(img->line_length), &(img->endian))) != NULL)
        {
                return (0);
        }
    }
    printf("\nWell, it doesn't work, shit");
    return (-1);
}
