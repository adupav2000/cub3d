/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:32:10 by AlainduPa         #+#    #+#             */
/*   Updated: 2021/04/20 19:41:10 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_color_from_tex(t_img *tex, int x, int y)
{
	if (x >= 0 && x <= tex->width && y >= 0 && y <= tex->height)
		return (*(int *)
			(tex->addr) + (y * tex->line_length + x * (tex->bpp / 8)));
	return (0x0);
}

int	load_texture(char *tex_link, t_img *img, t_data *mlx)
{
	if (ft_strncmp(&tex_link[ft_strlen(tex_link) - 3], "xpm", 3) == 0)
	{
		img->img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex_link,
				&img->width, &img->height);
		if (img->img == NULL)
			return (-1);
	}
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->line_length), &(img->endian));
	if (img->addr != NULL)
		return (0);
	return (-1);
}

int	handle_textures(char **line, t_map *map_info, t_data *data)
{
	int	i;

	i = 2;
	while (line[0][i] && line[0][i] == ' ')
		i++;
	if ((!ft_strncmp(line[0], "NO ", 3) && map_info->te_no.img != NULL)
		|| (!ft_strncmp(line[0], "SO ", 3) && map_info->te_so.img != NULL)
		|| (!ft_strncmp(line[0], "WE ", 3) && map_info->te_we.img != NULL)
		|| (!ft_strncmp(line[0], "S ", 3) && map_info->te_s.img != NULL)
		|| (!ft_strncmp(line[0], "EA ", 3) && map_info->te_ea.img != NULL))
		return (-1);
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
