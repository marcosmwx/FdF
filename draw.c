
#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

float    mod(float i)
{
    return (i < 0 ) ? -i : i;
}

void    bresehnam(float x, float y, int x1, int y1, fdf *data)
{
    float    x_step;
    float    y_step;
    int    max;

    x_step = x1 - x; // 2
    y_step = y1 - y; // 11

    max = MAX(MOD(x_step), MOD(y_step));
    x_step /= max;
    y_step /= max;
    while (1)
    {
         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xffffff);
         x+= x_step;
         y+= y_step;
    }
}