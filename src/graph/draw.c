/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:31:17 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:31:17 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

static void	isometric(float *x, float *y, int z, t_graph *graph)
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

static void	bresehnam(float x, float y, float x1, float y1, t_fdf *data, t_graph *graph, t_img *img_data)
{
	float	x_step;
	float	y_step;
	int		z;
	int		z1;
	int start_color;

	x_step = 0;
	y_step = 0;
	z = 0;
	z1 = 0;
	start_color = 0;

	get_initial_values(&z, &z1, &start_color, x, x1, y, y1, data);
	apply_scale_zoom(&x, &y, &x1, &y1, graph);
	apply_center_of_map(&x, &y, &x1, &y1, data, graph);
	isometric(&x, &y, z, graph);
	isometric(&x1, &y1, z1, graph);
	apply_shift(&x, &y, &x1, &y1, graph);
	trace_lines(&x_step, &y_step, x, y, &x1, &y1, data, img_data, start_color);
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
				bresehnam(x, y, x + 1, y, data, graph, img_data);
			if (y < data->height - 1)
				bresehnam(x, y, x, y + 1, data, graph, img_data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_data->img_ptr, 0, 0);
}
