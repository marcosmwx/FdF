/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferro-d <rferro-d@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:22:06 by rferro-d          #+#    #+#             */
/*   Updated: 2024/10/08 18:22:11 by rferro-d         ###   ########.fr       */
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
