#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MALLOC_ERROR	1
#define WIDTH		400
#define HEIGHT		400

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}		t_mlx_data;

int	key_hook(int keycode, t_mlx_data *data)
{
	if (keycode == 53 || keycode == 65307)
	{
		printf("Esc pressionado! Fechando...\n");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		exit(0);
	}
	else
	{
		printf("Tecla pressionada: %d\n", keycode);
	}
	return (0);
}

int	main(void)
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	return (MALLOC_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FdF - MwX-");
	if (data.win_ptr == NULL)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (MALLOC_ERROR);
	}

	mlx_key_hook(data.win_ptr, key_hook, &data);

	mlx_loop(data.mlx_ptr);	

	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

