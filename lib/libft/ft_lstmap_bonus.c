/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:27:21 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/31 17:27:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*index;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (0);
	output = ft_lstnew(f(lst->content));
	if (!output)
		return (0);
	index = lst;
	while (index->next)
	{
		index = index->next;
		tmp = ft_lstnew(f(index->content));
		if (!tmp)
		{
			ft_lstclear(&output, del);
			return (0);
		}
		ft_lstadd_back(&output, tmp);
	}
	return (output);
}
