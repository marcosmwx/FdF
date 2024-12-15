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
	z *= graph->depth_factor;
	rotated_y = previous_y * cos(graph->angle_x) - z * sin(graph->angle_x);
	rotated_z = previous_y * sin(graph->angle_x) + z * cos(graph->angle_x);
	rotated_x = previous_x * cos(graph->angle_y) + rotated_z
		* sin(graph->angle_y);
	rotated_z = -previous_x * sin(graph->angle_y) + rotated_z
		* cos(graph->angle_y);
	*x = rotated_x;
	*y = rotated_y;
}

static void	bresenham(t_coords coords, t_fdf_gen *gen_data)
{
	float	x_step;
	float	y_step;

	x_step = 0;
	y_step = 0;
	coords.z = 0;
	coords.z1 = 0;
	coords.start_color = 0;
	get_initial_values(&coords, gen_data->data);
	apply_scale_zoom(&coords, gen_data->graph);
	apply_center_of_map(&coords, gen_data);
	isometric(&coords.x, &coords.y, coords.z, gen_data->graph);
	isometric(&coords.x1, &coords.y1, coords.z1, gen_data->graph);
	apply_shift(&coords, gen_data->graph);
	trace_lines(&x_step, &y_step, &coords, gen_data);
}

static void	process_coords(t_coords *coords, t_fdf_gen *gen_data)
{
	if (coords->x < gen_data->data->width - 1)
	{
		coords->x1 = coords->x + 1;
		coords->y1 = coords->y;
		bresenham(*coords, gen_data);
	}
	if (coords->y < gen_data->data->height - 1)
	{
		coords->x1 = coords->x;
		coords->y1 = coords->y + 1;
		bresenham(*coords, gen_data);
	}
}

void	draw(t_fdf_gen *gen_data)
{
	t_coords	coords;

	clear_image(gen_data->data, gen_data->img_data);
	coords.y = 0;
	while (coords.y < gen_data->data->height)
	{
		coords.x = 0;
		while (coords.x < gen_data->data->width)
		{
			process_coords(&coords, gen_data);
			coords.x++;
		}
		coords.y++;
	}
	mlx_put_image_to_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr,
		gen_data->img_data->img_ptr, 0, 0);
}
