/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:29:12 by rferro-d          #+#    #+#             */
/*   Updated: 2024/11/25 20:05:25 by rferro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (c == 0)
		return ((char *)s + ft_strlen((char *)s));
	while (*s)
		if ((unsigned char)*s++ == (unsigned char)c)
			return ((char *)--s);
	return (NULL);
}
