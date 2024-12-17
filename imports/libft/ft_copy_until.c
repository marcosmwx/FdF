/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_until.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:16:17 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/17 12:47:36 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_copy_until(char *src, int n)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(sizeof(char) * (n + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (i <= n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
