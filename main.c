#include "cub3d.h"

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main(void)
{
    data_t          *data;
    t_map         *map_info;

    
    if (!(map_info = malloc(sizeof(t_map))) || !(data = malloc(sizeof(data_t))))
        return (-1);
    if (parsing(map_info, data))
        return (-1);
    if ((data->mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data->mlx_win = mlx_new_window(data->mlx_ptr, map_info->window_width, map_info->window_height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    void *test = map_info->te_no.img;
    write(1, &"hello\n", 6);
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, map_info->te_no.img, 0, 0);
    mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
