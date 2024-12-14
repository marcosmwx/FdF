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

void get_initial_values(t_coords *coords, t_fdf *data)
{
	// Acessa os valores z dentro dos blocos da matriz - valores iniciais
	coords->z = data->z_matrix[(int)(coords->y * data->width + coords->x)].value; // Acesso ao valor Z
	coords->z1 = data->z_matrix[(int)(coords->y1 * data->width + coords->x1)].value; // Acesso ao valor Z1
	coords->start_color = ft_atoi_hexa(data->z_matrix[(int)(coords->y * data->width + coords->x)].hex); // Acesso à cor inicial
}

void	apply_scale_zoom(t_coords *coords, t_graph *graph)
{
	//apply scale of zoom of any original value of scale
	coords->x *= graph->zoom;
	coords->y *= graph->zoom;
	coords->x1 *= graph->zoom;
	coords->y1 *= graph->zoom;
}

void	apply_center_of_map(t_coords *coords, t_fdf_gen *gen_data)
{
	//before any change we turn the view a center of map
	coords->x -= (gen_data->data->width - 1) * gen_data->graph->zoom / 2.0;
	coords->y -= (gen_data->data->height - 1) * gen_data->graph->zoom / 2.0;
	coords->x1 -= (gen_data->data->width - 1) * gen_data->graph->zoom / 2.0;
	coords->y1 -= (gen_data->data->height - 1) * gen_data->graph->zoom / 2.0;
}

void	apply_shift(t_coords *coords, t_graph *graph)
{
	// apply shift for render on center of view after change scale
	coords->x += graph->shift_x;
	coords->y += graph->shift_y;
	coords->x1 += graph->shift_x;
	coords->y1 += graph->shift_y;
}