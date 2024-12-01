#include "fdf.h"

// compilador
// gcc *.c libft/libft.a minilibx-linux/libmlx.a -lX11 -lXext -lm
// cc *.c libft/libft.a  src/free/free_data.c src/free/free_resources.c src/key/key_hook.c minilibx-linux/libmlx.a -lX11 -lXext -lm
static int	free_pointer_server(t_fdf_gen *gen_data)
{
    mlx_destroy_display(gen_data->data->mlx_ptr);
    free(gen_data->data->mlx_ptr);
    free_data(gen_data->data);
    return (1);
}

static void mlx_pack_hooks(t_fdf_gen *gen_data)
{
  	mlx_mouse_hook(gen_data->data->win_ptr, mouse_press, gen_data);
	mlx_hook(gen_data->data->win_ptr, 6, (1L << 6), mouse_move, gen_data);
	mlx_hook(gen_data->data->win_ptr, 17, 0, free_resources, gen_data);
	mlx_key_hook(gen_data->data->win_ptr, key_hook, gen_data);
}

static void make_img(t_fdf_gen *gen_data)
{
	gen_data->img_data->img_ptr = mlx_new_image(gen_data->data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	gen_data->img_data->img_data = mlx_get_data_addr(gen_data->img_data->img_ptr, &gen_data->img_data->bpp,
			&gen_data->img_data->size_line, &gen_data->img_data->endian);
    draw(gen_data->data, gen_data->graph, gen_data->img_data);
}

static void init_variables(t_fdf_gen gen_data)
{
 	gen_data.data->mlx_ptr = mlx_init();
	gen_data.data->win_ptr = mlx_new_window(gen_data.data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	gen_data.graph->zoom = 3;
	gen_data.graph->angle_x = 0.2;      // Valor inicial do ângulo X (radiano)
	gen_data.graph->angle_y = 0.2;      // Valor inicial do ângulo Y (radiano)
	gen_data.graph->depth_factor = 0.4; // Valor inicial da profundidade
    gen_data.mouse_set->mouse_pressed = 0;

	// Calculo de deslocamento para centralizar o mapa
	float map_center_x;
    map_center_x = (gen_data.data->width - 1) * gen_data.graph->zoom / 50.0;
	float map_center_y;
    map_center_y = (gen_data.data->height - 1) * gen_data.graph->zoom / 50.0;
	gen_data.graph->shift_x = (WIN_WIDTH / 2) - map_center_x;
	gen_data.graph->shift_y = (WIN_HEIGHT / 2) - map_center_y;
}

int	main(int argc, char **argv)
{
  	if (argc != 2)
    {
     	write(1, "Can't execute the program, the context dont have a map file\n", 59);
        return (0);
    }

	t_fdf_gen gen_data;
	gen_data.data = (t_fdf *)malloc(sizeof(t_fdf));
	gen_data.graph = (t_graph *)malloc(sizeof(t_graph));
	gen_data.mouse_set = (t_mouse *)malloc(sizeof(t_mouse));
	gen_data.img_data = (t_img *)malloc(sizeof(t_img));

     if (!read_file(argv[1], gen_data.data))
     {
		free_resources(&gen_data);
      	free_pointer_server(&gen_data);
     }
    init_variables(gen_data);
	make_img(&gen_data);
    mlx_pack_hooks(&gen_data);
	mlx_loop(gen_data.data->mlx_ptr);
    free_pointer_server(&gen_data);
}
