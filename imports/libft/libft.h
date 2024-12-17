/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:07 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/17 13:13:46 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>

int		ft_wdcounter(char const *s, char c);
int		ft_atoi(const char *nptr);
int		ft_atoi_hexa(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_copy_from(char *src, int n);
char	*ft_copy_until(char *src, int n);
char	*ft_strdup(const char *src);
void	ft_putstr(char *s);

#endif
