#include "fdf.h"

// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm

void    free_data(t_fdf **data)
{
    int i;

    i = 0;
    if (!(*data))
        return ;
    if ((*data)->z_matriz)
    {
        while (i < (*data)->height)
        {
            free((*data)->z_matriz[i]);
            i++;
        }
        free((*data)->z_matriz);
    }
	if ((*data))
    	free((*data));
    (*data) = NULL;
}

int	exit_with_safe(t_fdf_gen *gen_data)
{
	mlx_destroy_image(gen_data->data->mlx_ptr, gen_data->img_data->img_ptr);
	mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
	mlx_destroy_display(gen_data->data->mlx_ptr);
	free(gen_data->data->mlx_ptr);
	free_data(&gen_data->data);
	free(gen_data->graph);
	free(gen_data->mouse_set);
	free(gen_data->img_data);
	free(gen_data->color_set);
	free(gen_data);
	exit(0);
	return(1);
}

int	key_hook(int keycode, t_fdf_gen *gen_data)
{
	if (keycode == 65307 || keycode == 53)
	{
		// printf("Tecla %d - Esc pressionada! Fechando...\n", keycode);
		exit_with_safe(gen_data);
	}
	if (keycode == 105) // Tecla 'i' para aumentar a profundidade
		gen_data->graph->depth_factor += 10;
	if (keycode == 111) // Tecla 'o' para diminuir a profundidade
		gen_data->graph->depth_factor -= 10;
	if (keycode == 65362) // Seta para cima rotaciona para cima
		gen_data->graph->angle_x += 0.1;
	if (keycode == 65364) // Seta para baixo rotaciona para baixo
		gen_data->graph->angle_x -= 0.1;
	if (keycode == 65361) // Seta para esquerda rotaciona girando para esquerda
		gen_data->graph->angle_y -= 0.1;
	if (keycode == 65363) // Seta para direita rotaciona girando para direita
		gen_data->graph->angle_y += 0.1;
	if (keycode == 119) // tecla w movimenta para cima
		gen_data->graph->shift_y -= 10;
	if (keycode == 115) // tecla s movimenta para baixo
		gen_data->graph->shift_y += 10;
	if (keycode == 97) // tecla a movimenta para esquerda
		gen_data->graph->shift_x -= 10;
	if (keycode == 100) // tecla d movimenta para direita
		gen_data->graph->shift_x += 10;
	if (keycode == 122) // tecla z da zoom
		gen_data->graph->zoom += 10;
	if (keycode == 120) // tecla x diminui o zoom
		gen_data->graph->zoom -= 10;
	if (keycode == 99) // Tecla c para aumentar o fator de cor
		gen_data->color_set->color_factor += 10;
	if (keycode == 118) // Tecla c para diminuir o fator de cor
		gen_data->color_set->color_factor -= 10;
	draw(gen_data->data, gen_data->graph, gen_data->color_set, gen_data->img_data);
	printf("%d\n", keycode);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf_gen *gen_data;
	
	gen_data = (t_fdf_gen *)malloc(sizeof(t_fdf_gen));
	gen_data->data = (t_fdf *)malloc(sizeof(t_fdf));
	gen_data->graph = (t_graph *)malloc(sizeof(t_graph));
	gen_data->color_set = (t_color *)malloc(sizeof(t_color));
	gen_data->mouse_set = (t_mouse *)malloc(sizeof(t_mouse));
	gen_data->img_data = (t_img *)malloc(sizeof(t_img));

	if (!read_file(argv[1], gen_data->data))
		exit_with_safe(gen_data);

	gen_data->data->mlx_ptr = mlx_init();
	gen_data->data->win_ptr = mlx_new_window(gen_data->data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	gen_data->graph->zoom = 20;
	gen_data->graph->angle_x = 0.2;      // Valor inicial do ângulo X (radiano)
	gen_data->graph->angle_y = 0.2;      // Valor inicial do ângulo Y (radiano)
	gen_data->graph->depth_factor = 1.0; // Valor inicial da profundidade
	gen_data->color_set->color_factor = 100;

	// Calculo de deslocamento para centralizar o mapa
	float map_center_x = (gen_data->data->width - 1) * gen_data->graph->zoom / 50.0;
	float map_center_y = (gen_data->data->height - 1) * gen_data->graph->zoom / 50.0;

	gen_data->graph->shift_x = (WIN_WIDTH / 2) - map_center_x;
	gen_data->graph->shift_y = (WIN_HEIGHT / 2) - map_center_y;

	gen_data->mouse_set->mouse_pressed = 0;

	// Criar a imagem
	gen_data->img_data->img_ptr = mlx_new_image(gen_data->data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	// printf("gen_data->img_data->img_ptr: %p\n", gen_data->img_data->img_ptr);
	gen_data->img_data->img_data = mlx_get_data_addr(gen_data->img_data->img_ptr, &gen_data->img_data->bpp,
			&gen_data->img_data->size_line, &gen_data->img_data->endian);
	// printf("gen_data->img_data->img_data: %p\n", gen_data->img_data->img_data);

	// if (!gen_data->data->z_matriz == NULL)
	// 	exit_with_safe(gen_data);
	draw(gen_data->data, gen_data->graph, gen_data->color_set, gen_data->img_data);
	mlx_mouse_hook(gen_data->data->win_ptr, mouse_press, gen_data);
	mlx_hook(gen_data->data->win_ptr, 6, (1L << 6), mouse_move, gen_data);
	mlx_hook(gen_data->data->win_ptr, 17, 0, exit_with_safe, gen_data);
	mlx_key_hook(gen_data->data->win_ptr, key_hook, gen_data);
	// Movimento do mouse faz a rotação
	mlx_loop(gen_data->data->mlx_ptr);
}


