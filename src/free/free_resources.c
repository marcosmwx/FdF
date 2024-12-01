/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:15:09 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:15:09 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	free_resources(t_fdf_gen *gen_data)
{
    free(gen_data->graph);
    free(gen_data->mouse_set);
    free(gen_data->img_data);
    return(1);
}
