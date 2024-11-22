#include "fdf.h"
// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm

int	key_hook(int keycode, fdf *data)
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
    	data->depth_factor += 10;
	if (keycode == 111) // Tecla 'o' para diminuir a profundidade
    	data->depth_factor -= 10;
    if (keycode == 65362) // Seta para cima rotaciona para cima
        data->angle_x += 0.1;
    if (keycode == 65364) // Seta para baixo rotaciona para baixo
        data->angle_x -= 0.1;
    if (keycode == 65361) // Seta para esquerda rotaciona girando para esquerda
        data->angle_y -= 0.1;
    if (keycode == 65363) // Seta para direita rotaciona girando para direita
        data->angle_y += 0.1;
    if (keycode == 119) // tecla w movimenta para cima
		data->shift_y -= 10;
    if (keycode == 115) // tecla s movimenta para baixo
		data->shift_y += 10;
    if (keycode == 97) // tecla a movimenta para esquerda
    	data->shift_x -= 10;
    if (keycode == 100) // tecla d movimenta para direita
    	data->shift_x += 10;
    if (keycode == 122) //tecla z da zoom
      data->zoom += 10;
    if (keycode == 120) //tecla x diminui o zoom
      data->zoom -= 10;
	if (keycode == 99) // Tecla c para aumentar o fator de cor
		data->color_factor += 10;
	if (keycode == 118) // Tecla c para diminuir o fator de cor
		data->color_factor -= 10;

	draw(data);
   	printf("%d\n", keycode);
	return (0);
}

int    main(int argc, char **argv)
{
    fdf *data;

    data = (fdf*)malloc(sizeof(fdf));
    read_file(argv[1], data);

    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
    data->zoom = 20;
    data->angle_x = 0.2; // Valor inicial do ângulo X (radiano)
    data->angle_y = 0.2; // Valor inicial do ângulo Y (radiano)
    data->depth_factor = 1.0; // Valor inicial da profundidade
    data->color_factor = 100;

    // Calculo de deslocamento para centralizar o mapa
    float map_center_x = (data->width - 1) * data->zoom / 50.0;
    float map_center_y = (data->height - 1) * data->zoom / 50.0;

    data->shift_x = (WIN_WIDTH / 2) - map_center_x;
    data->shift_y = (WIN_HEIGHT / 2) - map_center_y;

    data->mouse_pressed = 0;

    // Criar a imagem
    data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    data->img_data = mlx_get_data_addr(data->img_ptr, &data->bpp, &data->size_line, &data->endian);

    draw(data);
    mlx_key_hook(data->win_ptr, key_hook, data);
    mlx_mouse_hook(data->win_ptr, mouse_press, data);
    mlx_hook(data->win_ptr, 6, (1L << 6), mouse_move, data); // Movimento do mouse faz a rotação
    mlx_loop(data->mlx_ptr);
}