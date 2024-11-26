#include "fdf.h"
#include <math.h>

#define MAX(a, b) (a > b ? a : b)
#define MOD(a) ((a < 0) ? -a : a)

int	calculate_color(int z, int z_min, int z_max, t_color *color_set)
{
	float	factor;
	int		red;
	int		green;
	int		blue;

	if (z <= 0)
		return (0x404040); // cor da base ...
	// Normaliza Z no intervalo
	factor = (float)(z - z_min) / (float)(z_max - z_min);
	if (factor > 1.0)
		factor = 1.0; // Garante que o fator não ultrapasse 1
	// Modifica a interpolação de cores usando o fator de cor
	factor *= (color_set->color_factor / 100.0);
		// Controlando a intensidade de cor com color_factor
	// Interpolação de cores (branco -> vermelho)
	red = (int)(0xFF * factor);
	green = (int)(0xFF * (1 - factor));
	blue = (int)(0xFF * (1 - factor));
	return ((red << 16) | (green << 8) | blue);
}

int	interpolate_color(int start_color, int end_color, float t)
{
	int	start_r;
	int	start_g;
	int	start_b;
	int	end_r;
	int	end_g;
	int	end_b;
	int	r;
	int	g;
	int	b;

	if (t > 1.0)
		t = 1.0; // Garante que o fator não ultrapasse o limite
	start_r = (start_color >> 16) & 0xFF;
	start_g = (start_color >> 8) & 0xFF;
	start_b = start_color & 0xFF;
	end_r = (end_color >> 16) & 0xFF;
	end_g = (end_color >> 8) & 0xFF;
	end_b = end_color & 0xFF;
	r = (int)(start_r + t * (end_r - start_r));
	g = (int)(start_g + t * (end_g - start_g));
	b = (int)(start_b + t * (end_b - start_b));
	return ((r << 16) | (g << 8) | b);
}

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

void	set_pixel(t_img *img_data, int x, int y, int color)
{
	int	index;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		index = (y * img_data->size_line + x * (img_data->bpp / 8));
		*(int *)(img_data->img_data + index) = color; // Define a cor do pixel
	}
}

void	bresehnam(float x, float y, float x1, float y1, t_fdf *data,  t_graph *graph,  t_color *color_set,  t_img   *img_data)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z_min;
	int		z_max;
	int		start_color;
	int		end_color;

	int z, z1;
	z = data->z_matriz[(int)y][(int)x];
	z1 = data->z_matriz[(int)y1][(int)x1];
	//------ zoom count ------//
	x *= graph->zoom;
	y *= graph->zoom;
	x1 *= graph->zoom;
	y1 *= graph->zoom;
	// Subtrair o centro do mapa para centralizar antes da rotação
	x -= (data->width - 1) * graph->zoom / 2.0;
	y -= (data->height - 1) * graph->zoom / 2.0;
	x1 -= (data->width - 1) * graph->zoom / 2.0;
	y1 -= (data->height - 1) * graph->zoom / 2.0;
	//------- 3D CALC -----//
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
	// Determina o valor mínimo e máximo de z para o degradê
	z_min = -50;
	z_max = 50;
	start_color = calculate_color(z, z_min, z_max, color_set);
	end_color = calculate_color(z1, z_min, z_max, color_set);
	float t = 0; // Fator de interpolação (de 0 a 1)
	while ((int)(x - x1) || (int)(y - y1))
	{
		t += 1.0 / max;                                          
			// Incrementa o fator proporcional ao passo
		int color = interpolate_color(start_color, end_color, t);
			// Calcula a cor interpolada
		set_pixel(img_data, (int)x, (int)y, color);                  
			// Define a cor do pixel na imagem
		x += x_step;
		y += y_step;
	}
}

#include <string.h>

void	clear_image(t_fdf *data, t_img *img_data)
{
	//free(img_data->img_ptr);
	mlx_destroy_image(data->mlx_ptr, img_data->img_ptr);
	img_data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img_data->img_data = mlx_get_data_addr(img_data->img_ptr, &img_data->bpp, &img_data->size_line, &img_data->endian);
}

void	draw(t_fdf *data,  t_graph *graph,  t_color *color_set,  t_img   *img_data)
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
				bresehnam(x, y, x + 1, y, data,  graph,  color_set, img_data);
			if (y < data->height - 1)
				bresehnam(x, y, x, y + 1, data,  graph,  color_set,  img_data);
			x++;
		}
		y++;
	}
	// Exibir a imagem na janela
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_data->img_ptr, 0, 0);
}