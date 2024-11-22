#include "fdf.h"

// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm


int	key_hook(int keycode, t_fdf *data, t_graph *graph, t_color *color_set, t_img *img_data)
{
	if (keycode == 65307 || keycode == 53)
	{
		printf("Tecla %d - Esc pressionada! Fechando...\n", keycode);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	if (keycode == 105) // Tecla 'i' para aumentar a profundidade
		graph->depth_factor += 10;
	if (keycode == 111) // Tecla 'o' para diminuir a profundidade
		graph->depth_factor -= 10;
	if (keycode == 65362) // Seta para cima rotaciona para cima
		graph->angle_x += 0.1;
	if (keycode == 65364) // Seta para baixo rotaciona para baixo
		graph->angle_x -= 0.1;
	if (keycode == 65361) // Seta para esquerda rotaciona girando para esquerda
		graph->angle_y -= 0.1;
	if (keycode == 65363) // Seta para direita rotaciona girando para direita
		graph->angle_y += 0.1;
	if (keycode == 119) // tecla w movimenta para cima
		graph->shift_y -= 10;
	if (keycode == 115) // tecla s movimenta para baixo
		graph->shift_y += 10;
	if (keycode == 97) // tecla a movimenta para esquerda
		graph->shift_x -= 10;
	if (keycode == 100) // tecla d movimenta para direita
		graph->shift_x += 10;
	if (keycode == 122) // tecla z da zoom
		graph->zoom += 10;
	if (keycode == 120) // tecla x diminui o zoom
		graph->zoom -= 10;
	if (keycode == 99) // Tecla c para aumentar o fator de cor
		color_set->color_factor += 10;
	if (keycode == 118) // Tecla c para diminuir o fator de cor
		color_set->color_factor -= 10;

	draw(data, graph, color_set, img_data);
	printf("%d\n", keycode);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf *data;
	t_graph *graph;
	t_color *color_set;
	t_mouse *mouse_set;
	t_img   *img_data;

	
	data = (t_fdf *)malloc(sizeof(t_fdf));
	graph = (t_graph *)malloc(sizeof(t_graph));
	color_set = (t_color *)malloc(sizeof(t_color));
	mouse_set = (t_mouse *)malloc(sizeof(t_mouse));
	img_data = (t_img *)malloc(sizeof(t_img));


	read_file(argv[1], data);

	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	graph->zoom = 20;
	graph->angle_x = 0.2;      // Valor inicial do ângulo X (radiano)
	graph->angle_y = 0.2;      // Valor inicial do ângulo Y (radiano)
	graph->depth_factor = 1.0; // Valor inicial da profundidade
	color_set->color_factor = 100;

	// Calculo de deslocamento para centralizar o mapa
	float map_center_x = (data->width - 1) * graph->zoom / 50.0;
	float map_center_y = (data->height - 1) * graph->zoom / 50.0;

	graph->shift_x = (WIN_WIDTH / 2) - map_center_x;
	graph->shift_y = (WIN_HEIGHT / 2) - map_center_y;

	mouse_set->mouse_pressed = 0;

	// Criar a imagem
	img_data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img_data->img_data = mlx_get_data_addr(img_data->img_ptr, &img_data->bpp,
			&img_data->size_line, &img_data->endian);

	draw(data, graph, color_set, img_data);
	//mlx_mouse_hook(data->win_ptr, mouse_press, data);
	mlx_hook(data->win_ptr, 6, (1L << 6), mouse_move, data);
		// Movimento do mouse faz a rotação
	mlx_loop(data->mlx_ptr);
}


