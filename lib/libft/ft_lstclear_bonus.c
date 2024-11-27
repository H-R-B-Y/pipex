/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:22:48 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/05 15:50:56 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	if (!lst || !*lst || !del)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	del((*lst)->content);
	free(*lst);
	*lst = 0;
}
