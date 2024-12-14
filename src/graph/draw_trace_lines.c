/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_trace_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:31:06 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:31:06 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

static int	max_func(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

static float	mod(float i)
{
	if (i < 0)
		i = -i;
	return (i);
}

static void	set_pixel(t_coords *coords, t_fdf_gen *gen_data)
{
	int	index;

	index = 0;
	if (coords->x >= 0 && coords->x < gen_data->data->win_width
		&& coords->y >= 0 && coords->y < gen_data->data->win_height)
	{
		index = ((int)coords->y * gen_data->img_data->size_line
				+ (int)coords->x * (gen_data->img_data->bpp / 8));
		*(int *)(gen_data->img_data->img_data + index) = coords->start_color;
	}
}

void	trace_lines(float *x_step, float *y_step,
		t_coords *coords, t_fdf_gen *gen_data)
{
	int		max;

	max = 0;
	*x_step = coords->x1 - coords->x;
	*y_step = coords->y1 - coords->y;
	max = max_func(mod(*x_step), mod(*y_step));
	*x_step /= max;
	*y_step /= max;
	while ((int)(coords->x - coords->x1) || (int)(coords->y - coords->y1))
	{
		set_pixel(coords, gen_data);
		coords->x += *x_step;
		coords->y += *y_step;
	}
}
