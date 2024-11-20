#include "fdf.h"
// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

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
    if (keycode == 119)
		data->shift_y -= 10;
    if (keycode == 115)
		data->shift_y += 10;
    if (keycode == 97)
    	data->shift_x -= 10;
    if (keycode == 100)
    	data->shift_x += 10;
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
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
	// Calcule o deslocamento para centralizar o mapa
	float map_center_x = (data->width - 1) * data->zoom / 4;
	float map_center_y = (data->height - 1) * data->zoom / 2.0;

	data->shift_x = (WIN_WIDTH / 2) - map_center_x;
	data->shift_y = (WIN_HEIGHT / 2) - map_center_y;

	draw(data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
}
