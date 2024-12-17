/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:01 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:01 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"
#include "keycodes.h"
#include <stdio.h>

static void	handle_depth(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == KEY_I)
		gen_data->graph->depth_factor += 0.4;
	else if (keycode == KEY_O)
		gen_data->graph->depth_factor -= 0.4;
}

static void	handle_rotation(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == KEY_UP)
		gen_data->graph->angle_x += 0.1;
	else if (keycode == KEY_DOWN)
		gen_data->graph->angle_x -= 0.1;
	else if (keycode == KEY_LEFT)
		gen_data->graph->angle_y -= 0.1;
	else if (keycode == KEY_RIGHT)
		gen_data->graph->angle_y += 0.1;
}

static void	handle_movement(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == KEY_W)
		gen_data->graph->shift_y -= 10;
	else if (keycode == KEY_S)
		gen_data->graph->shift_y += 10;
	else if (keycode == KEY_A)
		gen_data->graph->shift_x -= 10;
	else if (keycode == KEY_D)
		gen_data->graph->shift_x += 10;
}

static void	handle_zoom(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == KEY_Z)
	{
		if (gen_data->graph->zoom < 21 && gen_data->graph->zoom >= 3)
			gen_data->graph->zoom += 1;
	}
	else if (keycode == KEY_X)
	{
		if (gen_data->graph->zoom > 3 && gen_data->graph->zoom <= 21)
			gen_data->graph->zoom -= 1;
	}
}

int	key_hook(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == KEY_ESC || keycode == KEY_ESC_ALT)
		return (mlx_loop_end(gen_data->data->mlx_ptr));
	handle_depth(keycode, gen_data);
	handle_rotation(keycode, gen_data);
	handle_movement(keycode, gen_data);
	handle_zoom(keycode, gen_data);
	draw(gen_data);
	return (0);
}
