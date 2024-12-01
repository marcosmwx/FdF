#include "../../fdf.h"

static int fill_value_and_color(char *num_str, t_point *z_line)
{
	char **value_and_color;
		
	value_and_color = ft_split(num_str, ','); // Separa valor e cor
	if (!value_and_color)
		return (0);
	z_line->value = ft_atoi(value_and_color[0]); // Primeiro elemento é o valor Z
	if (value_and_color[1])		// Verifica se há cor definida
		z_line->hex = ft_strdup(value_and_color[1]); // Duplica a cor para o hex
	else
		z_line->hex = ft_strdup("0xFFFFFF"); // Cor padrão (branco)
	free(value_and_color[0]);
    if (value_and_color[1])
        free(value_and_color[1]);
    free(value_and_color);
	return (1);
}

static void    fill_matrix(t_point *z_line, char *line, int width)
{
	char    **nums;
	int     i;

    i = 0;
	nums = ft_split(line, ' '); // Divide a linha em posix
	if (!nums)
	{
		free(nums);//talvez remover ou por o de dar free antes
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
}

static void	init_get_resources_from_file(t_fdf *data, char *file_name)
{
	data->height = get_height(file_name);
	data->width = get_width(file_name);
}

int read_file(char *file_name, t_fdf *data)
{
	int     fd;
	int     i;
	char    *line;

	init_get_resources_from_file(data, file_name);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * data->height);
	if (!data->z_matrix)
		return (0);
	i = -1;
	while (++i < data->height)
	{
		data->z_matrix[i] = (t_point *)malloc(sizeof(t_point) * data->width);
		if (!data->z_matrix[i])
			return (0);
	}
	fd = open(file_name, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		fill_matrix(data->z_matrix[i], line, data->width);
		free(line);
		i++;
	}
	close(fd);
	return (1);
}
