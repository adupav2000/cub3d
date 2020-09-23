#include "cub3d.h"


int main()
{
     data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (-1);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
        return (-1);
    mlx_loop(data.mlx_ptr);
    return (0);                        
        
}
