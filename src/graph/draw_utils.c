/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:31:13 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:31:13 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	get_initial_values(t_coords *coords, t_fdf *data)
{
	coords->z = data->z_matrix[
		(int)(coords->y * data->width + coords->x)].value;
	coords->z1 = data->z_matrix[
		(int)(coords->y1 * data->width + coords->x1)].value;
	coords->start_color = ft_atoi_hexa(data->z_matrix[
			(int)(coords->y * data->width + coords->x)].hex);
}

void	apply_scale_zoom(t_coords *coords, t_graph *graph)
{
	coords->x *= graph->zoom;
	coords->y *= graph->zoom;
	coords->x1 *= graph->zoom;
	coords->y1 *= graph->zoom;
}

void	apply_center_of_map(t_coords *coords, t_fdf_gen *gen_data)
{
	coords->x -= (gen_data->data->width - 1) * gen_data->graph->zoom / 2.0;
	coords->y -= (gen_data->data->height - 1) * gen_data->graph->zoom / 2.0;
	coords->x1 -= (gen_data->data->width - 1) * gen_data->graph->zoom / 2.0;
	coords->y1 -= (gen_data->data->height - 1) * gen_data->graph->zoom / 2.0;
}

void	apply_shift(t_coords *coords, t_graph *graph)
{
	coords->x += graph->shift_x;
	coords->y += graph->shift_y;
	coords->x1 += graph->shift_x;
	coords->y1 += graph->shift_y;
}
