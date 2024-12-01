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

static int max_func(int a, int b) {
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

static float	mod(float i)
{
	if (i < 0)
		i = -i;
	return (i);
}

static void	set_pixel(t_fdf *data, t_img *img_data, int x, int y, int color)
{
	int	index;

	index = 0;
	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		index = (y * img_data->size_line + x * (img_data->bpp / 8));
		*(int *)(img_data->img_data + index) = color; // Define a cor do pixel
	}
}

void	trace_lines(float *x_step, float *y_step, float x, float y, float *x1, float *y1, t_fdf *data, t_img *img_data, int start_color)
{
	int		max;
	
	max = 0;
	*x_step = *x1 - x;
	*y_step = *y1 - y;
	max = max_func(mod(*x_step), mod(*y_step));
	*x_step /= max;
	*y_step /= max;
	// draw lines with the colors
	while ((int)(x - *x1) || (int)(y - *y1))
	{
		// Define the color of  pixel using the color of initial point
		set_pixel(data, img_data, (int)x, (int)y, start_color);
		x += *x_step;
		y += *y_step;
	}
}