#include "cub3d.h"

int main(void)
{
    data_t        data;
    t_map         *map_info;

    map_info = malloc(sizeof(t_map));
    parsing(map_info, &data);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, map_info->window_width, map_info->window_height, "Hello world")) == NULL)
        return (EXIT_FAILURE);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
