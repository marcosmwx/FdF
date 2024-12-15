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

static void	handle_depth(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 105) // Tecla 'i' para aumentar a profundidade
		gen_data->graph->depth_factor += 0.4;
	else if (keycode == 111) // Tecla 'o' para diminuir a profundidade
		gen_data->graph->depth_factor -= 0.4;
}

static void	handle_rotation(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 65362) // Seta para cima rotaciona para cima
		gen_data->graph->angle_x += 0.1;
	else if (keycode == 65364) // Seta para baixo rotaciona para baixo
		gen_data->graph->angle_x -= 0.1;
	else if (keycode == 65361) // Seta para esquerda rotaciona girando para esquerda
		gen_data->graph->angle_y -= 0.1;
	else if (keycode == 65363) // Seta para direita rotaciona girando para direita
		gen_data->graph->angle_y += 0.1;
}

static void	handle_movement(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 119) // tecla w movimenta para cima
		gen_data->graph->shift_y -= 10;
	else if (keycode == 115) // tecla s movimenta para baixo
		gen_data->graph->shift_y += 10;
	else if (keycode == 97) // tecla a movimenta para esquerda
		gen_data->graph->shift_x -= 10;
	else if (keycode == 100) // tecla d movimenta para direita
		gen_data->graph->shift_x += 10;
}

static void	handle_zoom(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 122) // tecla z aumenta zoom
		gen_data->graph->zoom += 5;
	else if (keycode == 120) // tecla x diminui zoom
		gen_data->graph->zoom -= 5;
}

int	key_hook(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 65307 || keycode == 53) // Tecla ESC para sair
		return (mlx_loop_end(gen_data->data->mlx_ptr));
	handle_depth(keycode, gen_data);
	handle_rotation(keycode, gen_data);
	handle_movement(keycode, gen_data);
	handle_zoom(keycode, gen_data);
	draw(gen_data);
	return (0);
}
