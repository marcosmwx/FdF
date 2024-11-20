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
    int    zoom;
    int    color;
    int    shift_x;
    int    shift_y;
    float	angle_x;
    float	angle_y;
    float   depth_factor;

    void    *mlx_ptr;
    void    *win_ptr;
}    fdf;

void    read_file(char *file_name, fdf *data);
void    bresehnam(float x, float y, float x1, float y1, fdf *data);
void    draw(fdf *data);

#endif
