/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:37:45 by malopes-          #+#    #+#             */
/*   Updated: 2024/10/21 10:34:18 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

static char	*extract_line(char **buffer)
{
	int		i;
	char	*line;
	char	*remaining;

	i = 0;
	if (!*buffer)
		return (NULL);
	if (ft_strchr(*buffer, '\n'))
	{
		while ((*buffer)[i] != '\0')
		{
			if ((*buffer)[i] == '\n')
			{
				line = ft_copy_until(*buffer, i);
				if (!line)
					return (NULL);
				remaining = ft_copy_from(*buffer, i + 1);
				free(*buffer);
				*buffer = remaining;
				return (line);
			}
			i++;
		}
	}
	return (NULL);
}

static char	*process_final_buffer(char **buffer, int bytes_read)
{
	char	*line;

	if (bytes_read == 0 && *buffer != NULL)
	{
		if (ft_strchr(*buffer, '\n'))
			return (extract_line(buffer));
		if (**buffer != '\0')
		{
			line = ft_copy_until(*buffer, ft_strlen(*buffer));
			free(*buffer);
			*buffer = NULL;
			return (line);
		}
	}
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

static char	*process_reading(int fd, char *temp, char **buffer)
{
	int		bytes_read;
	char	*line;

	bytes_read = read(fd, temp, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, temp);
		if (!*buffer)
			return (NULL);
		line = extract_line(buffer);
		if (line)
			return (line);
		bytes_read = read(fd, temp, BUFFER_SIZE);
	}
	return (process_final_buffer(buffer, bytes_read));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp;
	char		*line;

	temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp || fd < 0 || BUFFER_SIZE <= 0)
	{
		free(temp);
		return (NULL);
	}
	line = process_reading(fd, temp, &buffer);
	free(temp);
	return (line);
}
