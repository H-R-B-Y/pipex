/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:38:36 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/23 18:01:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	read_ln_heredoc(char *endstr, int child_input, int child_output)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(endstr);
	tmp = get_next_line(child_input);
	while (tmp)
	{
		if (tmp && !ft_strncmp(tmp, endstr, len))
		{
			free(tmp);
			close(child_input);
			close(child_output);
			return ;
		}
		ft_putstr_fd(tmp, child_output);
		free(tmp);
		tmp = get_next_line(child_input);
	}
	close(child_input);
	close(child_output);
	return ;
}

int	setup_heredoc(char *endstr, int *io_fds)
{
	int	child_writes[2];
	int	pid;

	pipe(child_writes);
	pid = fork();
	if (pid <= -1)
		perror("pipe");
	else if (!pid)
	{
		close(child_writes[0]);
		read_ln_heredoc(endstr, STDIN_FILENO, child_writes[1]);
		exit(0);
	}
	else
	{
		close(child_writes[1]);
		io_fds[0] = child_writes[0];
	}
	return (pid);
}
