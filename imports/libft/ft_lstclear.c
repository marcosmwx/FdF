/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:16:37 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:16:37 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*it;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		it = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = it;
	}
}
