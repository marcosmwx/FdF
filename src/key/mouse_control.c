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

int	mouse_move(int x, int y, t_fdf_gen *gen_data)
{
	int	dx;
	int	dy;

	// Só rotaciona se o botão do mouse estiver pressionado
	if (gen_data->mouse_set->mouse_pressed == 1)
	{
		// Calcula a diferença de movimento
		dx = x - gen_data->mouse_set->last_mouse_x;
		dy = y - gen_data->mouse_set->last_mouse_y;
		// Se houver movimento, aplica rotação
		if (dx != 0 || dy != 0)
		{
			// Atualiza os ângulos com base no movimento do mouse
			gen_data->graph->angle_x += dy * 0.005; // Sensibilidade para o eixo X
			gen_data->graph->angle_y += dx * 0.005; // Sensibilidade para o eixo Y
			// Atualiza a posição do mouse para a próxima iteração
			gen_data->mouse_set->last_mouse_x = x;
			gen_data->mouse_set->last_mouse_y = y;
			// Redesenha a janela com a nova rotação
			// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Limpa a janela
			draw(gen_data->data, gen_data->graph, gen_data->img_data); // Desenha o mapa com a rotação aplicada
		}
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_fdf_gen *gen_data)
{
	printf("Botão pressionado: %d\n", button);
	if (button == 1)
	{                            // Botão esquerdo do mouse
		gen_data->mouse_set->mouse_pressed = 1; // Marca que o botão esquerdo foi pressionado
		gen_data->mouse_set->last_mouse_x = x;  // Armazena a posição inicial do mouse
		gen_data->mouse_set->last_mouse_y = y;
	}
	else if (button == 3)
	{                            // Botão direito do mouse
		gen_data->mouse_set->mouse_pressed = 0; // Marca que o botão direito foi pressionado
	}
	return (0);
}
