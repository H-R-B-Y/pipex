/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:32:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/28 12:15:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	cleanup(int fds[2], int pipe[2], t_list *lst, char *error)
{
	if (fds)
	{
		if (fds[0] > 2)
			close(fds[0]);
		if (fds[1] > 2)
			close(fds[1]);
	}
	if (pipe)
	{
		if (pipe[0] > 2)
			close(pipe[0]);
		if (pipe[1] > 2)
			close(pipe[1]);
	}
	ft_lstclear(&lst, (void (*)(void *))ft_deletesplit);
	if (error)
	{
		perror(error);
		exit(1);
	}
}

int	exit_clause(int err)
{
	if (err)
		ft_putendl_fd(PUSAGE, STDERR_FILENO);
	return (err);
}
