/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:15:34 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/02 15:01:07 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int draw_floor_and_ceiling(t_img img_to_change, int x, int y_begin, int len,
    t_map *map_info)
{
    int i;

    i = 0;
    if ((x > img_to_change.width) || (x < 0) ||(y_begin < 0) 
            ||(len < 0) ||((len + y_begin) > img_to_change.height))
        return (-1);
    while (i < y_begin)
        my_mlx_pixel_put(&img_to_change, x, i++, map_info->color_ceiling);
    i += len;
    while (i < map_info->window_height)
        my_mlx_pixel_put(&img_to_change, x, i++, map_info->color_floor);
    return (0); 
}

int drawVertLineFromColor(t_img img_to_change, int x, int y_begin,
    int len, int color)
{
    int i;

    i = 0;
    if ((x > img_to_change.width) || (x < 0) ||(y_begin < 0) 
            ||(len < 0) ||((len + y_begin) > img_to_change.height))
        return (-1);
    //printf("ERROR x : %d, img_to_change.width %d, y_begin : %d, len %d, img_to_change.height %d\n", x, img_to_change.width, y_begin, len, img_to_change.height);

    //printf("Everything left right x : %d, img_to_change.width %d, y_begin : %d, len %d, img_to_change.height %d\n", x, img_to_change.width, y_begin, len, img_to_change.height);
    while (len)
        my_mlx_pixel_put(&img_to_change, x, (y_begin + len--), color);
    return (0);
}
