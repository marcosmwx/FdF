/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:55 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:55 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

void	free_data(t_fdf *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (data->z_matrix)
	{
		while (i < data->height * data->width)
		{
			if (data->z_matrix[i].hex)
				free(data->z_matrix[i].hex);
			i++;
		}
		free(data->z_matrix);
	}
	free(data);
	data = NULL;
}
