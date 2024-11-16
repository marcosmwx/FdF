#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>

static int	ft_wdcounter(char const *s, char c)
{
    int	i;
    int	j;

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

int get_height(char *file_name)
{
    char *line;
    int fd;
    int height;

    fd = open(file_name, O_RDONLY, 0);
    if (fd < 0)
        return -1;
    height = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        height++;
        free(line);
    }
    close(fd);
    return height;
}


int    get_width(char *file_name)
{
     int    width;
     int    fd;
     char    *line;

     fd = open(file_name, O_RDONLY, 0);
     line = get_next_line(fd);
     if (line == NULL)
       write(1, "Erro line get_width", 19);

     width = ft_wdcounter(line, ' '); //word counter
     free(line);
     close(fd);
     return (width);
}

void    fill_matriz(int *z_line, char *line, int width)
{
        char **nums;
        int     i;

        i = 0;
        nums = ft_split(line, ' ');
        if (!nums) {
            write(1, "Erro: ft_split retornou NULL.\n", 30);
            return;
        }
        while (nums[i] && i < width)
        {
             z_line[i] = ft_atoi(nums[i]);
             free(nums[i]);
             i++;
        }
        free(nums);
}

void    read_file(char *file_name, fdf *data)
{
    int    fd;
    int    i;
    char   *line;

    data->height = get_height(file_name);
    data->width = get_width(file_name);
    data->z_matriz = (int **)malloc(sizeof(int*) * data->height);
    if (!data->z_matriz)
    {
        write(1, "Erro malloc z_matriz", 20);
        return;
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
