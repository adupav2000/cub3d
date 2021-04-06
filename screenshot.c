/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 19:15:41 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/06 13:01:49 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_int_in_char(unsigned char *dest, int value)
{
	dest[0] = (unsigned char)(value);
	dest[1] = (unsigned char)(value >> 8);
	dest[2] = (unsigned char)(value >> 16);
	dest[3] = (unsigned char)(value >> 24);
}

int write_file_header(int fd, int file_size, t_map *map)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = 0;
	bmpfileheader[0] = (unsigned char)'B';
	bmpfileheader[1] = (unsigned char)'M';
	put_int_in_char(bmpfileheader + 2, file_size);
	bmpfileheader[10] = (unsigned char)54;
	bmpfileheader[14] = (unsigned char)40;
	put_int_in_char(bmpfileheader + 18, map->window_width);
	put_int_in_char(bmpfileheader + 22, map->window_height);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	if (write(fd, bmpfileheader, 54) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int get_color(t_img *img, int x, int y)
{
	int	rgb;
	int	color;

    // color = *(int *)(img->addr + (y * img->line_length + x * (	img->bpp / 8)));
	color = *(int*)(img->addr
			+ (4 * (int)img->width * ((int)img->height - 1 - y))
			+ (4 * x));
	printf("%x ", color);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

/*w being the image of the file*/
static int write_screen_data(int file, t_img *w, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	printf("w->height : %d, w->width : %d\n", w->height, w->width);
	printf("pad ; %d\n", pad);
	while (i < (int)w->height)
	{
		j = 0;
		while (j < (int)w->width)
		{
			color = get_color(w, j, i);
			if (write(file, &color, 3) < 0)
			{
				printf("color = %d", color);
				return (-1);
			}
			if (pad > 0 && write(file, &zero, pad) < 0)
			{
				printf("pad = %d", pad);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int write_and_save_screen(t_game *game)
{
	int filesize;
	int fd;
	int pad;

	pad = (4 - ((int)game->map_info.window_width * 3) % 4) % 4;
	filesize = 54  + (3 * ((int)game->map_info.window_width + pad)
		* (int)game->map_info.window_height);
	if ((fd = open("screenshot.bmp",  (O_WRONLY | O_CREAT), 0666)) < 0)
		{
			printf("error 1\n");
			return (-1);
		}
	if (write_file_header(fd, filesize, &(game->map_info)))
	{
		printf("error 2\n");
		return (-1);
	}
	if (write_screen_data(fd, &(game->player.current_image), pad))
	{
		printf("error 3\n");
		return (-1);
	}
	close(fd);
	return (EXIT_SUCCESS);
}