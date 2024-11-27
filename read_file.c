#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>


static int	ft_wdcounter(char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (j);
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

int calculate_line_width(char *line) {
	if (!line)
		return -1;
	return ft_wdcounter(line, ' ');
}

int check_line_width_consistency(int fd, int width) {
	char *line;
	int current_width;

	while ((line = get_next_line(fd)) != NULL) {
		current_width = calculate_line_width(line);
		if (current_width != width) {
			write(1, "Erro: Linhas com larguras inconsistentes.\n", 43);
			free(line);
			return -1;
		}
		free(line);
	}
	return width;
}

int get_width(char *file_name)
{
	int fd;
	char *line;
	int width;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return 0;
	line = get_next_line(fd);
	if (line == NULL)// talvez tirar
    {
		write(1, "Erro: Arquivo vazio em get_width.\n", 34);
		close(fd);
		return 0;
	}
	if (!line)
		return -1;
	width = ft_wdcounter(line, ' ');
	free(line);
	if (check_line_width_consistency(fd, width) == -1)
    {
		close(fd);
		return 0;
	}
	close(fd);
	return width;
}

void	fill_matriz(int *z_line, char *line, int width)
{
	char **nums;
	int i;

	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
	{
		write(1, "Erro: ft_split retornou NULL.\n", 30);
		return ;
	}
	while (nums[i] && i < width)
	{
		z_line[i] = ft_atoi(nums[i]);
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	read_file(char *file_name, t_fdf *data)
{
	int fd;
	int i;
	char *line;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->z_matriz = (int **)malloc(sizeof(int *) * data->height);
	if (!data->z_matriz)
	{
		write(1, "Erro malloc z_matriz", 20);
		return ;
	}
	i = -1;
	while (++i < data->height)
		data->z_matriz[i] = (int *)malloc(sizeof(int) * (data->width));
	fd = open(file_name, O_RDONLY, 0);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		fill_matriz(data->z_matriz[i], line, data->width);
		free(line);
		i++;
	}
	close(fd);
}
