/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:15:25 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:15:25 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// isometric
// key states

static void	mlx_pack_hooks(t_fdf_gen *gen_data)
{
	mlx_mouse_hook(gen_data->data->win_ptr, mouse_press, gen_data);
	mlx_hook(gen_data->data->win_ptr, 6, (1L << 6), mouse_move, gen_data);
	mlx_hook(gen_data->data->win_ptr, 17, 0, mlx_loop_end, gen_data->data->mlx_ptr);
	mlx_key_hook(gen_data->data->win_ptr, key_hook, gen_data);
}

static void	make_img(t_fdf_gen *gen_data)
{
	gen_data->img_data->img_ptr = mlx_new_image(gen_data->data->mlx_ptr, gen_data->data->win_width, gen_data->data->win_height);
	gen_data->img_data->img_data = mlx_get_data_addr(gen_data->img_data->img_ptr, &gen_data->img_data->bpp,
			&gen_data->img_data->size_line, &gen_data->img_data->endian);
	draw(gen_data->data, gen_data->graph, gen_data->img_data);
}

static void init_variables(t_fdf_gen *gen_data)
{
	float map_center_x;
	float map_center_y;

    map_center_x = 0;
	map_center_y = 0;
	gen_data->graph->zoom = 3;
	gen_data->graph->angle_x = 0.2;
	gen_data->graph->angle_y = 0.2;
	gen_data->graph->depth_factor = 0.4;
	gen_data->mouse_set->mouse_pressed = 0;
	map_center_x = (gen_data->data->width - 1) * gen_data->graph->zoom / 50.0;
	map_center_y = (gen_data->data->height - 1) * gen_data->graph->zoom / 50.0;
	gen_data->graph->shift_x = (gen_data->data->win_width / 2) - map_center_x;
	gen_data->graph->shift_y = (gen_data->data->win_height / 2) - map_center_y;
}

static int	start_server(t_fdf_gen *gen_data)
{
	gen_data->data->mlx_ptr = mlx_init();
	if (!gen_data->data->mlx_ptr)
		return (0);
	gen_data->data->win_width = -1;
	gen_data->data->win_height = -1;
	gen_data->data->win_ptr = NULL;
    mlx_get_screen_size(gen_data->data->mlx_ptr, &gen_data->data->win_width, &gen_data->data->win_height);
	if (gen_data->data->win_width < 0 || gen_data->data->win_height < 0)
		return(0);
	gen_data->data->win_ptr = mlx_new_window(gen_data->data->mlx_ptr, gen_data->data->win_width, gen_data->data->win_height, "FdF");
	if (!gen_data->data->win_ptr)
		return (0);
	init_variables(gen_data);
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf_gen gen_data;

	if (argc != 2)
	{
		ft_putstr(NF_MAP);
		return (0);
	}
	gen_data.data = (t_fdf *)malloc(sizeof(t_fdf));
	gen_data.graph = (t_graph *)malloc(sizeof(t_graph));
	gen_data.mouse_set = (t_mouse *)malloc(sizeof(t_mouse));
	gen_data.img_data = (t_img *)malloc(sizeof(t_img));
	if (!read_file(argv[1], gen_data.data))
	{
		free_resources(&gen_data);
		free_pointer_server(&gen_data);
		return (0);
	}
	if(start_server(&gen_data))
	{
		make_img(&gen_data);
		mlx_pack_hooks(&gen_data);
		mlx_loop(gen_data.data->mlx_ptr);
	}
	free_pointer_server(&gen_data);
	free_resources(&gen_data);
}
