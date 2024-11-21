#include "fdf.h"

int mouse_move(int x, int y, fdf *data)
{
    // Só rotaciona se o botão do mouse estiver pressionado
    if (data->mouse_pressed == 1) {
        // Calcula a diferença de movimento
        int dx = x - data->last_mouse_x;
        int dy = y - data->last_mouse_y;

        // Se houver movimento, aplica rotação
        if (dx != 0 || dy != 0) {
            // Atualiza os ângulos com base no movimento do mouse
            data->angle_x += dy * 0.005;  // Sensibilidade para o eixo X
            data->angle_y += dx * 0.005;  // Sensibilidade para o eixo Y

            // Atualiza a posição do mouse para a próxima iteração
            data->last_mouse_x = x;
            data->last_mouse_y = y;

            // Redesenha a janela com a nova rotação
            mlx_clear_window(data->mlx_ptr, data->win_ptr); // Limpa a janela
            draw(data);  // Desenha o mapa com a rotação aplicada
        }
    }
    return 0;
}

int mouse_press(int button, int x, int y, fdf *data)
{
    printf("Botão pressionado: %d\n", button);
    if (button == 1) {  // Botão esquerdo do mouse
        data->mouse_pressed = 1;  // Marca que o botão esquerdo foi pressionado
        data->last_mouse_x = x;   // Armazena a posição inicial do mouse
        data->last_mouse_y = y;
    }
    else if (button == 3) {  // Botão direito do mouse
        data->mouse_pressed = 0;  // Marca que o botão direito foi pressionado
    }
    return 0;
}
