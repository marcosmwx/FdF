/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointer_server.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:15:01 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:15:01 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	free_pointer_server(t_fdf_gen *gen_data)
{
	if (!gen_data->data)
		return (0);
	if (gen_data->data->mlx_ptr && gen_data->data->win_ptr)
	{
		mlx_destroy_image(gen_data->data->mlx_ptr, gen_data->img_data->img_ptr);
		mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
		gen_data->data->win_ptr = NULL;
	}
	if (gen_data->data->mlx_ptr)
	{
		mlx_destroy_display(gen_data->data->mlx_ptr);
		free(gen_data->data->mlx_ptr);
		gen_data->data->mlx_ptr = NULL;
	}
	if (gen_data->data)
		free_data(gen_data->data);
	gen_data->data = NULL;
	return (0);
}
