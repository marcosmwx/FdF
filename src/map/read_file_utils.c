/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:14:28 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:14:28 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	check_line_width_consistency(int fd, int width)
{
	char *line;
	int current_width;

	while ((line = get_next_line(fd)) != NULL)
	{
		current_width = ft_wdcounter(line, ' ');
		if (current_width != width)
		{
			write(1, "Erro: Linhas com larguras inconsistentes.\n", 43);
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	return (width);
}

int	get_height(char *file_name)
{
	char *line;
	int fd;
	int height;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	int fd;
	char *line;
	int width;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (line == NULL)
	{
		write(1, "Erro: Arquivo vazio em get_width.\n", 34);
		close(fd);
		return (0);
	}
	width = ft_wdcounter(line, ' ');
	free(line);
	if (check_line_width_consistency(fd, width) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (width);
}
