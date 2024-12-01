#include "fdf.h"

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

int	get_width(char *file_name)
{
	int fd;
	char *line;
	int width;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (line == NULL) // talvez tirar
	{
		write(1, "Erro: Arquivo vazio em get_width.\n", 34);
		close(fd);
		return (0);
	}
	if (!line)
		return (-1);
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

void    fill_matriz(t_point *z_line, char *line, int width)
{
	char    **nums;
	int     i;

    i = 0;
	nums = ft_split(line, ' '); // Divide a linha em posix
	if (!nums)
	{
		write(1, "Erro: ft_split retornou NULL.\n", 30);
		return ;
	}
	while (nums[i] && i < width)
	{
		char **value_and_color = ft_split(nums[i], ','); // Separa valor e cor
        if (!value_and_color)
        {
          write(1, "Erro: ft_split retornou NULL[2].\n", 30);
          free(nums[i]);
          continue;
        }
		z_line[i].value = ft_atoi(value_and_color[0]);   // Primeiro elemento é o valor Z
		// Verifica se há cor definida
		if (value_and_color[1])
			z_line[i].hex = ft_strdup(value_and_color[1]); // Duplica a cor para o hex
		else
			z_line[i].hex = ft_strdup("0xFFFFFF"); // Cor padrão (branco)

		free(value_and_color[0]);
		if (value_and_color[1])
			free(value_and_color[1]);
		free(value_and_color);
		free(nums[i]);
		i++;
	}
	free(nums);
}

int read_file(char *file_name, t_fdf *data)
{
	int     fd;
	int     i;
	char    *line;

	data->height = get_height(file_name);
	data->width = get_width(file_name);

	// Aloca matriz de t_point
	data->z_matriz = (t_point **)malloc(sizeof(t_point *) * data->height);
	if (!data->z_matriz)
	{
		write(1, "Erro malloc z_matriz", 20);
		return (0);
	}
	i = -1;
	while (++i < data->height)
		data->z_matriz[i] = (t_point *)malloc(sizeof(t_point) * data->width);

	fd = open(file_name, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		fill_matriz(data->z_matriz[i], line, data->width);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}
