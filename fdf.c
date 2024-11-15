#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MALLOC_ERROR	1
#define WIDTH		400
#define HEIGHT		400

int main(void)
{
    void *mlx_connection;
    void *mlx_window;

    mlx_connection = mlx_init();
    if (NULL == mlx_connection)
        return (MALLOC_ERROR);

    mlx_window = mlx_new_window(mlx_connection, WIDTH, HEIGHT, "My window");
    if (NULL == mlx_window)
    {
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return (MALLOC_ERROR);
    }

    mlx_loop(mlx_connection);
    mlx_destroy_window(mlx_connection, mlx_window);
    mlx_destroy_display(mlx_connection);
    free(mlx_connection);
    return (0);
}
