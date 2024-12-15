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

void	free_resources(t_fdf_gen *gen_data)
{
	if (gen_data->img_data)
		free(gen_data->img_data);
	if (gen_data->graph)
		free(gen_data->graph);
	if (gen_data->data)
		free(gen_data->data);
}
