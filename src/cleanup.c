/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:32:12 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/07 14:59:56 by hbreeze          ###   ########.fr       */
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
	{
		ft_putendl_fd(PUSAGE, STDERR_FILENO);
		ft_putendl_fd("Add: append_ before input for append (>>)", STDERR_FILENO);
		ft_putstr_fd("Add: here_doc {HEREDOC} instead of", STDOUT_FILENO);
		ft_putendl_fd("input for here doc pipe (<<)", STDERR_FILENO);
		ft_putstr_fd("Add: append_doc {HEREDOC} instead ", STDOUT_FILENO);
		ft_putendl_fd("of input for here doc and append", STDERR_FILENO);
	}
	return (err);
}
