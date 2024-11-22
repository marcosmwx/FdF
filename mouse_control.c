#include "fdf.h"

int	mouse_move(int x, int y,t_fdf *data, t_graph *graph, t_color *color_set,
	t_mouse *mouse_set,	t_img   *img_data)
{
	int	dx;
	int	dy;

	// Só rotaciona se o botão do mouse estiver pressionado
	if (mouse_set->mouse_pressed == 1)
	{
		// Calcula a diferença de movimento
		dx = x - mouse_set->last_mouse_x;
		dy = y - mouse_set->last_mouse_y;
		// Se houver movimento, aplica rotação
		if (dx != 0 || dy != 0)
		{
			// Atualiza os ângulos com base no movimento do mouse
			graph->angle_x += dy * 0.005; // Sensibilidade para o eixo X
			graph->angle_y += dx * 0.005; // Sensibilidade para o eixo Y
			// Atualiza a posição do mouse para a próxima iteração
			mouse_set->last_mouse_x = x;
			mouse_set->last_mouse_y = y;
			// Redesenha a janela com a nova rotação
			// mlx_clear_window(data->mlx_ptr, data->win_ptr); // Limpa a janela
			draw(data, graph, color_set, img_data); // Desenha o mapa com a rotação aplicada
		}
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_mouse *mouse_set)
{
	printf("Botão pressionado: %d\n", button);
	if (button == 1)
	{                            // Botão esquerdo do mouse
		mouse_set->mouse_pressed = 1; // Marca que o botão esquerdo foi pressionado
		mouse_set->last_mouse_x = x;  // Armazena a posição inicial do mouse
		mouse_set->last_mouse_y = y;
	}
	else if (button == 3)
	{                            // Botão direito do mouse
		mouse_set->mouse_pressed = 0; // Marca que o botão direito foi pressionado
	}
	return (0);
}
