#include "fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

// Função para interpolar cor com base em Z
int calculate_color(int z, int z_min, int z_max)
{
    if (z <= 0)
        return 0x404040; //cor da base ..

    // Interpolar entre branco e vermelho
    float factor = (float)(z - z_min) / (float)(z_max - z_min); // Normaliza Z no intervalo
    if (factor > 1.0)
        factor = 1.0; // Garante que o fator não ultrapasse 1

    // Interpolação de cores (branco -> vermelho)
    int red = (int)(0xFF * factor);        // Intensidade do vermelho
    int green = (int)(0xFF * (1 - factor)); // Reduz o verde conforme o vermelho aumenta
    int blue = (int)(0xFF * (1 - factor));  // Reduz o azul conforme o vermelho aumenta

    return (red << 16) | (green << 8) | blue; // Combina R, G, B em um valor hexadecimal
}

int interpolate_color(int start_color, int end_color, float t)
{
    if (t > 1.0)
        t = 1.0; // Garante que o fator não ultrapasse o limite

    int start_r = (start_color >> 16) & 0xFF;
    int start_g = (start_color >> 8) & 0xFF;
    int start_b = start_color & 0xFF;

    int end_r = (end_color >> 16) & 0xFF;
    int end_g = (end_color >> 8) & 0xFF;
    int end_b = end_color & 0xFF;

    int r = (int)(start_r + t * (end_r - start_r));
    int g = (int)(start_g + t * (end_g - start_g));
    int b = (int)(start_b + t * (end_b - start_b));

    return (r << 16) | (g << 8) | b;
}

void    isometric(float *x, float *y, int z, fdf *data)
{
    float previous_x = *x;
    float previous_y = *y;

    // Aplicando o fator de profundidade
    z *= data->depth_factor;

    // Rotação em torno do eixo X
    float rotated_y = previous_y * cos(data->angle_x) - z * sin(data->angle_x);
    float rotated_z = previous_y * sin(data->angle_x) + z * cos(data->angle_x);

    // Rotação em torno do eixo Y (se necessário)
    float rotated_x = previous_x * cos(data->angle_y) + rotated_z * sin(data->angle_y);
    rotated_z = -previous_x * sin(data->angle_y) + rotated_z * cos(data->angle_y);

    // Atualizando as coordenadas
    *x = rotated_x;  // X rotacionado em torno de Y
    *y = rotated_y;  // Y rotacionado em torno de X
}


float    mod(float i)
{
    if (i < 0)
      i = -i;
    return (i);
}

void bresehnam(float x, float y, float x1, float y1, fdf *data)
{
    float x_step;
    float y_step;
    int max;
    int z, z1;

    z = data->z_matriz[(int)y][(int)x];
    z1 = data->z_matriz[(int)y1][(int)x1];

    //------ zoom count ------//
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;

    // Subtrair o centro do mapa para centralizar antes da rotação
    x -= (data->width - 1) * data->zoom / 2.0;
    y -= (data->height - 1) * data->zoom / 2.0;
    x1 -= (data->width - 1) * data->zoom / 2.0;
    y1 -= (data->height - 1) * data->zoom / 2.0;

    //------- 3D CALC -----//
    isometric(&x, &y, z, data);
    isometric(&x1, &y1, z1, data);

    // Agora, deslocar de volta para o centro da tela
    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;

    x_step = x1 - x;
    y_step = y1 - y;
    max = MAX(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;

    // Determina o valor mínimo e máximo de z para o degradê
    int z_min = -50; // Ajuste conforme seu mapa
    int z_max = 50;

    int start_color = calculate_color(z, z_min, z_max);
    int end_color = calculate_color(z1, z_min, z_max);

    float t = 0; // Fator de interpolação (de 0 a 1)

    while ((int)(x - x1) || (int)(y - y1))
    {
        t += 1.0 / max; // Incrementa o fator proporcional ao passo
        int color = interpolate_color(start_color, end_color, t); // Calcula a cor interpolada
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
        x += x_step;
        y += y_step;
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
