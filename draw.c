#include "fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

void    isometric(float *x, float *y, int z)
{
    *x = (*x - *y ) * cos(0.8);
    *y = (*y + z ) * sin(0.8) - z;
}

float    mod(float i)
{
    return (i < 0 ) ? -i : i;
}

void    bresehnam(float x, float y, float x1, float y1, fdf *data)
{
    float    x_step;
    float    y_step;
    int    max;
    int    z;
    int    z1;

    z = data->z_matriz[(int)y][(int)x];
    z1 = data->z_matriz[(int)y1][(int)x1];

    //------ zoom count ------//
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;

    //------- Coloring --------//
    data->color = (z || z1) ? 0xe80c0c : 0xffffff;

    //----- 3D CALC -----//
    isometric(&x, &y, z);
    isometric(&x1, &y1, z1);

    //----- shift -------//
    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;

    x_step = x1 - x; // -2
    y_step = y1 - y; // -11
    max = MAX(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(x - x1) || (int)(y - y1))
    {
         mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
         x+= x_step;
         y+= y_step;
    }
}

void    draw(fdf *data)
{
    int    x;
    int    y;

    y = 0;
    while(y < data->height)
    {
        x = 0;
        while(x < data->width)
        {
            if (x < data->width - 1)
                bresehnam(x, y, x + 1, y, data);
            if (y < data->height - 1)
                bresehnam(x, y, x, y + 1, data);
            x++;
        }
        y++;
    }
}
