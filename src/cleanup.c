/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:32:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/20 16:33:13 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	cleanup(int fds[2], t_list *lst)
{
	close(fds[0]);
	close(fds[1]);
	ft_lstclear(&lst, (void (*)(void *))ft_deletesplit);
}

int	exit_clause(int err)
{
	if (err)
		ft_putendl_fd(PUSAGE, STDERR_FILENO);
	return (err);
}
