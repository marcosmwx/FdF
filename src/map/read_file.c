/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:38 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:38 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

static int	fill_value_and_color(char *num_str, t_point *z_line)
{
	char	**value_and_color;

	value_and_color = ft_split(num_str, ',');
	if (!value_and_color)
		return (0);
	z_line->value = ft_atoi(value_and_color[0]);
	if (value_and_color[1])
		z_line->hex = ft_strdup(value_and_color[1]);
	else
		z_line->hex = ft_strdup("0xFFFFFF");
	free(value_and_color[0]);
	if (value_and_color[1])
		free(value_and_color[1]);
	free(value_and_color);
	return (1);
}

static void	fill_matrix(t_point *z_line, char *line, int width)
{
	char	**nums;
	int		i;

	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
	{
		free(nums);
		return ;
	}
	while (nums[i] && i < width)
	{
		if (!fill_value_and_color(nums[i], &z_line[i]))
		{
			free(nums[i]);
			i++;
			continue ;
		}
		free(nums[i]);
		i++;
	}
	free(nums);
	free(line);
}

static int	init_get_resources_from_file(t_fdf *data, char *file_name)
{
	data->height = get_height(file_name);
	data->width = get_width(file_name);
	if (data->width <= 0 || data->height <= 0)
		return (0);
	return (1);
}

int	read_file(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	i = -1;
	if (!init_get_resources_from_file(data, file_name))
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	data->z_matrix = (t_point *)malloc(sizeof(t_point) * data->height
			* data->width);
	if (!data->z_matrix)
		return (0);
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		fill_matrix(&data->z_matrix[i * data->width], line, data->width);
	}
	close(fd);
	return (1);
}
