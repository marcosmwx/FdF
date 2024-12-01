/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:17:00 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:17:00 by malopes-         ###   ########.fr       */
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
