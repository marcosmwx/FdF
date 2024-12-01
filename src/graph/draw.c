#include "../../fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

void	isometric(float *x, float *y, int z, t_graph *graph)
{
	float	previous_x;
	float	previous_y;
	float	rotated_y;
	float	rotated_z;
	float	rotated_x;

	previous_x = *x;
	previous_y = *y;
	// Aplicando o fator de profundidade
	z *= graph->depth_factor;
	// Rotação em torno do eixo X
	rotated_y = previous_y * cos(graph->angle_x) - z * sin(graph->angle_x);
	rotated_z = previous_y * sin(graph->angle_x) + z * cos(graph->angle_x);
	// Rotação em torno do eixo Y (se necessário)
	rotated_x = previous_x * cos(graph->angle_y) + rotated_z
		* sin(graph->angle_y);
	rotated_z = -previous_x * sin(graph->angle_y) + rotated_z
		* cos(graph->angle_y);
	// Atualizando as coordenadas
	*x = rotated_x; // X rotacionado em torno de Y
	*y = rotated_y; // Y rotacionado em torno de X
}

float	mod(float i)
{
	if (i < 0)
		i = -i;
	return (i);
}

void	set_pixel(t_fdf *data, t_img *img_data, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		index = (y * img_data->size_line + x * (img_data->bpp / 8));
		*(int *)(img_data->img_data + index) = color; // Define a cor do pixel
	}
}

void	bresehnam(float x, float y, float x1, float y1, t_fdf *data, t_graph *graph, t_img *img_data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z, z1;
	int start_color;

	// Obtém os valores de Z para os pontos
	z = data->z_matriz[(int)y][(int)x].value;
	z1 = data->z_matriz[(int)y1][(int)x1].value;
	// Obtém as cores dos pontos diretamente da estrutura
	start_color = strtol(data->z_matriz[(int)y][(int)x].hex, NULL, 16);  // Converte a cor hex para um valor inteiro

	// ------ zoom count ------ //
	x *= graph->zoom;
	y *= graph->zoom;
	x1 *= graph->zoom;
	y1 *= graph->zoom;
	// Subtrair o centro do mapa para centralizar antes da rotação
	x -= (data->width - 1) * graph->zoom / 2.0;
	y -= (data->height - 1) * graph->zoom / 2.0;
	x1 -= (data->width - 1) * graph->zoom / 2.0;
	y1 -= (data->height - 1) * graph->zoom / 2.0;
	// ------- 3D CALC ----- //
	isometric(&x, &y, z, graph);
	isometric(&x1, &y1, z1, graph);
	// Agora, deslocar de volta para o centro da tela
	x += graph->shift_x;
	y += graph->shift_y;
	x1 += graph->shift_x;
	y1 += graph->shift_y;
	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	// Desenhar linha com as cores dos pontos
	while ((int)(x - x1) || (int)(y - y1))
	{
		set_pixel(data, img_data, (int)x, (int)y, start_color);  // Define a cor do pixel usando a cor do ponto inicial
		x += x_step;
		y += y_step;
	}
}

#include <string.h>

void	clear_image(t_fdf *data, t_img *img_data)
{
	mlx_destroy_image(data->mlx_ptr, img_data->img_ptr);
	img_data->img_ptr = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
	img_data->img_data = mlx_get_data_addr(img_data->img_ptr, &img_data->bpp, &img_data->size_line, &img_data->endian);
}

void	draw(t_fdf *data, t_graph *graph, t_img *img_data)
{
	clear_image(data, img_data);
	int x;
	int y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresehnam(x, y, x + 1, y, data, graph, img_data);  // Passa diretamente para a função
			if (y < data->height - 1)
				bresehnam(x, y, x, y + 1, data, graph, img_data);  // Passa diretamente para a função
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_data->img_ptr, 0, 0);
}
