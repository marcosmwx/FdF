/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:59:59 by malopes-          #+#    #+#             */
/*   Updated: 2024/10/09 17:41:44 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\v'
        || c == '\n' || c == '\r' || c == '\f')
        return (1);
    return (0);
}

int	ft_atoi(const char *nptr)
{
    int	sign;
    int	c;
    int	result;

    sign = 1;
    c = 0;
    result = 0;
    while (is_space(nptr[c]))
        c++;
    while (nptr[c] == '-' || nptr[c] == '+')
    {
        if (nptr[c] == '-')
            sign *= -1;
        if (nptr[c + 1] == '-' || nptr[c + 1] == '+')
            return (0);
        c++;
    }
    while (nptr[c] >= '0' && nptr[c] <= '9')
    {
        result = (result * 10) + (nptr[c] - '0');
        c++;
    }
    return (sign * result);
}
/*
#include <stdlib.h>
int	main(void)
{
    printf("%d\n", ft_atoi(" -a-10a"));
    printf("%d\n", atoi(" -a-10a"));
    return (0);
}
*/