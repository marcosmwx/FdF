/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:52:10 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/17 12:56:17 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
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

static char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	ft_allocw(char **new, char *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (start != i)
		{
			new[j] = ft_strndup(s + start, i - start);
			j++;
		}
	}
	new[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**new;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	new = (char **)malloc(sizeof(char *) * (words + 1));
	if (!new)
		return (NULL);
	ft_allocw(new, (char *)s, c);
	return (new);
}
