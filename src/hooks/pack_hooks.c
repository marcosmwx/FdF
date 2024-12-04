/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:10:26 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 22:10:26 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	pack_hooks(t_fdf_gen *gen_data)
{
    mlx_hook(gen_data->data->win_ptr, 4, (1L << 2), set_mouse_down, gen_data); // Mouse Down
    mlx_hook(gen_data->data->win_ptr, 5, (1L << 3), set_mouse_up, gen_data);   // Mouse Up
    mlx_hook(gen_data->data->win_ptr, 6, (1L << 6), mouse_move_event, gen_data);
	mlx_hook(gen_data->data->win_ptr, 17, 0, mlx_loop_end, gen_data->data->mlx_ptr);
	mlx_key_hook(gen_data->data->win_ptr, key_hook, gen_data);
}