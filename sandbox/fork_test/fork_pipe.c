/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:00:33 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 13:13:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int	p_pipe[2];
	int	pid;

	if (pipe(p_pipe))
		exit((perror("Failed to create pipe!\n"), 1));
	pid = fork();

	if (!pid) // Child process!
	{
		char t;
		int b_break = 0;
		close(p_pipe[0]);
		while (read(0, &t, 1))
		{
			if (t != '\n')
				write(p_pipe[1], &t, 1);
			else if (write(p_pipe[1], &t, 1), !b_break++)
				continue ;
			else if (b_break && t == '\n')
				break ;
			b_break = 0;
		}
		close(p_pipe[1]);
		exit(0);
	}
	else
	{
		char t;
		int stat = 1;
		close(p_pipe[1]);
		wait(&stat);
		while(read(p_pipe[0], &t, 1))
		{
			if (!t)
				break ;
			else
				write(1, &t, 1);
		}
		close(p_pipe[0]);
		exit(0);
	}
}