/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:15:34 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/03/24 16:28:55 by AlainduPa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int drawVertLineFromColor(t_img img_to_change, int x, int y_begin, int len, 
        int color)
{
    if ((x > img_to_change.width) || (x < 0) ||(y_begin < 0) 
            ||(len < 0) ||((len + y_begin) > img_to_change.height))
    {
        printf("ERROR x : %d, img_to_change.width %d, y_begin : %d, len %d, img_to_change.height %d\n", x, img_to_change.width, y_begin, len, img_to_change.height);
        return (-1);
    }
        //printf("Everything left right x : %d, img_to_change.width %d, y_begin : %d, len %d, img_to_change.height %d\n", x, img_to_change.width, y_begin, len, img_to_change.height);
    while (len)
        my_mlx_pixel_put(&img_to_change, x, (y_begin + len--), color);
    return (0);
}
