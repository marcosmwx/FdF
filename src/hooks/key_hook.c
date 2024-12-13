/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:01 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:01 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	key_hook(int keycode, t_fdf_gen *gen_data)
{
    if (keycode == 65307 || keycode == 53)
        return (mlx_loop_end(gen_data->data->mlx_ptr));
        //return(free_resources(gen_data));
    if (keycode == 105) // Tecla 'i' para aumentar a profundidade
        gen_data->graph->depth_factor += 0.4;
    if (keycode == 111) // Tecla 'o' para diminuir a profundidade
        gen_data->graph->depth_factor -= 0.4;
    if (keycode == 65362) // Seta para cima rotaciona para cima
        gen_data->graph->angle_x += 0.1;
    if (keycode == 65364) // Seta para baixo rotaciona para baixo
        gen_data->graph->angle_x -= 0.1;
    if (keycode == 65361) // Seta para esquerda rotaciona girando para esquerda
        gen_data->graph->angle_y -= 0.1;
    if (keycode == 65363) // Seta para direita rotaciona girando para direita
        gen_data->graph->angle_y += 0.1;
    if (keycode == 119) // tecla w movimenta para cima
        gen_data->graph->shift_y -= 10;
    if (keycode == 115) // tecla s movimenta para baixo
        gen_data->graph->shift_y += 10;
    if (keycode == 97) // tecla a movimenta para esquerda
        gen_data->graph->shift_x -= 10;
    if (keycode == 100) // tecla d movimenta para direita
        gen_data->graph->shift_x += 10;
    if (keycode == 122) // tecla z da zoom
        gen_data->graph->zoom += 5;
    if (keycode == 120) // tecla x diminui o zoom
        gen_data->graph->zoom -= 5;
    draw(gen_data);
    printf("%d\n", keycode);
    return (0);
}