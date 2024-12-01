/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:08:03 by rferro-d          #+#    #+#             */
/*   Updated: 2024/10/08 18:25:18 by rferro-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*it;

	if (lst == NULL)
		return (NULL);
	it = lst;
	while (lst != NULL)
	{
		it = lst;
		lst = lst->next;
	}
	return (it);
}
