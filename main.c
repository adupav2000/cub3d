#include "cub3d.h"
typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}          t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
    t_data  img;
    data_t        data;
    t_map         *map_info;

    
    if (!(map_info = malloc(sizeof(t_map))))
        return (-1);
    if (!parsing(map_info, &data))
        return (-1);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, map_info->window_width, map_info->window_height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    int i = 0;
    int i_1 = 0;
    while (i < 50)
        while (i_1 < 40)
            my_mlx_pixel_put(img.img, i++, i_1++, 0x00FF0000);
    mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, img.img, 0, 0);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
