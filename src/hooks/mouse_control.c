/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:14 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:14 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int set_mouse_up(int button, int x, int y, void *param) {
	t_fdf_gen *gen_data;

	(void)x;
	(void)y;
	gen_data = (t_fdf_gen *)param;
	if (!gen_data || !gen_data->mouse_set) {
		write(2, "Erro: param é NULL em set_mouse_up\n", 35);
		return (0);
	}

	if (button == 1) {
		write(1, "Mouse up detected\n", 18);
		gen_data->mouse_set->click_active = 0;
	}
	return (0);
}

int set_mouse_down(int button, int x, int y, void *param) {
	t_fdf_gen *gen_data;

	gen_data = (t_fdf_gen *)param;
	if (!gen_data || !gen_data->mouse_set) {
		write(2, "Erro: param é NULL em set_mouse_down\n", 36);
		return (0);
	}

	if (button == 1) {
		write(1, "Mouse press\n", 13);
		gen_data->mouse_set->click_active = 1;
		gen_data->mouse_set->last_mouse_x = x;
		gen_data->mouse_set->last_mouse_y = y;
	}
	return (0);
}

int mouse_move_event(int x, int y, void *param) 
{
	t_fdf_gen *gen_data;
	int dx;
	int dy;

	gen_data = (t_fdf_gen *)param;
	if (!gen_data || !gen_data->mouse_set || !gen_data->graph) {
		write(2, "Erro: param ou graph é NULL em mouse_move_event\n", 49);
		return (0);
	}
	if (!gen_data->mouse_set->click_active)
		return (0);
	dx = x - gen_data->mouse_set->last_mouse_x;
	dy = y - gen_data->mouse_set->last_mouse_y;

	if (dx != 0 || dy != 0) {
		gen_data->graph->angle_x += dy * 0.005;
		gen_data->graph->angle_y += dx * 0.005;
		gen_data->mouse_set->last_mouse_x = x;
		gen_data->mouse_set->last_mouse_y = y;
		draw(gen_data);
	}
	return (0);
}
