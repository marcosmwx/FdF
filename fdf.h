#ifndef FDF_H
# define FDF_H

#include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct
{
    int    width;
    int    height;
    int    **z_matriz;

    void    *mlx_ptr;
    void    *win_ptr;
}    fdf;

void    read_file(char *file_name, fdf *data);

#endif
