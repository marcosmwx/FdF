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

static void	make_img(t_fdf_gen *gen_data)
{
	gen_data->img_data->img_ptr = mlx_new_image(
			gen_data->data->mlx_ptr,
			gen_data->data->win_width,
			gen_data->data->win_height
			);
	gen_data->img_data->img_data = mlx_get_data_addr(
			gen_data->img_data->img_ptr,
			&gen_data->img_data->bpp,
			&gen_data->img_data->size_line,
			&gen_data->img_data->endian
			);
	draw(gen_data);
}

static void	set_variables(t_fdf_gen *gen_data)
{
	float	map_center_x;
	float	map_center_y;

	map_center_x = 0;
	map_center_y = 0;
	gen_data->graph->zoom = 4;
	gen_data->graph->angle_x = 0.2;
	gen_data->graph->angle_y = 0.2;
	gen_data->graph->depth_factor = 0.4;
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
	gen_data->data->win_width = 1920;
	gen_data->data->win_height = 1080;
	gen_data->data->win_ptr = NULL;
	mlx_get_screen_size(gen_data->data->mlx_ptr, &gen_data->data->win_width,
		&gen_data->data->win_height);
	if (gen_data->data->win_width < 0 || gen_data->data->win_height < 0)
		return (0);
	gen_data->data->win_ptr = mlx_new_window(
			gen_data->data->mlx_ptr,
			gen_data->data->win_width,
			gen_data->data->win_height,
			"FdF"
			);
	if (!gen_data->data->win_ptr)
		return (0);
	set_variables(gen_data);
	return (1);
}

static int	malloc_structs(t_fdf_gen *gen_data)
{
	gen_data->data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!gen_data->data)
	{
		free_resources(gen_data);
		return (0);
	}
	gen_data->graph = (t_graph *)malloc(sizeof(t_graph));
	if (!gen_data->graph)
	{
		free_resources(gen_data);
		return (0);
	}
	gen_data->img_data = (t_img *)malloc(sizeof(t_img));
	if (!gen_data->img_data)
	{
		free_resources(gen_data);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf_gen	gen_data;

	if (argc != 2)
	{
		ft_putstr(NF_MAP);
		return (0);
	}
	if (!malloc_structs(&gen_data))
		return (0);
	if (!read_file(argv[1], gen_data.data))
	{
		free_resources(&gen_data);
		return (0);
	}
	if (start_server(&gen_data))
	{
		make_img(&gen_data);
		pack_hooks(&gen_data);
		mlx_loop(gen_data.data->mlx_ptr);
	}
	free_pointer_server(&gen_data);
	free_resources(&gen_data);
}
