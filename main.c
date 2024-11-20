#include "fdf.h"
// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm

#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

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
    if (keycode == 65362) // Seta para cima
        data->angle_x += 0.1;
    if (keycode == 65364) // Seta para baixo
        data->angle_x -= 0.1;
    if (keycode == 65361) // Seta para esquerda
        data->angle_y -= 0.1;
    if (keycode == 65363) // Seta para direita
        data->angle_y += 0.1;
    if (keycode == 119)
		data->shift_y -= 10;
    if (keycode == 115)
		data->shift_y += 10;
    if (keycode == 97)
    	data->shift_x -= 10;
    if (keycode == 100)
    	data->shift_x += 10;
    if (keycode == 122)
      data->zoom += 10;
    if (keycode == 120)
      data->zoom -= 10;


    mlx_clear_window(data->mlx_ptr, data->win_ptr);
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
	// Calcule o deslocamento para centralizar o mapa
	float map_center_x = (data->width - 1) * data->zoom / 2.0;
	float map_center_y = (data->height - 1) * data->zoom / 2.0;

	data->shift_x = (WIN_WIDTH / 2) - map_center_x;
	data->shift_y = (WIN_HEIGHT / 2) - map_center_y;

	draw(data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
}
