/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_from.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:37:59 by malopes-          #+#    #+#             */
/*   Updated: 2024/10/21 10:19:01 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_copy_from(char *src, int n)
{
	char	*dest;
	int		i;

	if (src == NULL || src[n] == '\0')
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(src + n) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[n + i] != '\0')
	{
		dest[i] = src[n + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
