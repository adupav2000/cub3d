/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:15:34 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/14 13:44:14 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void sprite_pixel_put(t_game *game, t_img *tex, int x, int y)
{
    t_img *curr_img;
    int r;
    int g;
    int b;

    curr_img = &(game->player.current_image);
    r = tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8)];
    g =  tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8) + 1];
    b = tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8) + 2];
    // if((r & 0x00FFFFFF) == 0 && (g & 0x00FFFFFF) == 0 && (b & 0x00FFFFFF) == 0)
    // {
        curr_img->addr[y * curr_img->line_length 
            + x * curr_img->bpp / 8] = r;
        curr_img->addr[y * curr_img->line_length 
            + x * curr_img->bpp / 8 + 1] = g;
        curr_img->addr[y * curr_img->line_length 
            + x * curr_img->bpp / 8 + 2] = b;
    // } 
}

void texture_pixel_put(t_game *game, t_img *tex, int x, int y)
{
    t_img *curr_img;

    curr_img = &(game->player.current_image);
    curr_img->addr[y * curr_img->line_length + x * curr_img->bpp / 8] = 
        tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8)];
    curr_img->addr[y * curr_img->line_length + x * curr_img->bpp / 8 + 1] = 
        tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8) + 1];
    curr_img->addr[y * curr_img->line_length + x * curr_img->bpp / 8 + 2] = 
        tex->addr[game->player.texY * tex->line_length 
        + game->player.texX * (tex->bpp / 8) + 2];
}

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
    // printf("hello x : %d, img_to_change.width : %d, y_begin : %d, len : %d, img_to_change.height : %d\n", x, img_to_change.width, y_begin, len, img_to_change.height);
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
    while (len)
        my_mlx_pixel_put(&img_to_change, x, (y_begin + len--), color);
    return (0);
}
