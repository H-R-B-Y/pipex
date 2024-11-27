/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-25 16:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-25 16:38:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

extern char **environ;

void	child_process_prep(int n, t_cmddesc cmd, int io_fd[2], int pipe[2])
{
	if (n > 1)
	{
		dup2(pipe[1], STDOUT_FILENO); // Redirect output to pipe
		close(pipe[0]);
		close(pipe[1]);
	}
	else
		dup2(io_fd[1], STDOUT_FILENO); // Last command writes to output file
	dup2(io_fd[0], STDIN_FILENO); // Input redirection
	close(io_fd[0]);
	execve(cmd[0], &cmd[0], environ);
}

int	execute_commands(int n, t_list *cmdv, int input_fd, int output_fd)
{
	int pipe_fd[2];
	pid_t pid;
	int status;

	if (n == 0)
		return (0); // Base case: no more commands
	if (n > 1) // Only create a pipe if there's a next command
		pipe(pipe_fd);
	status = 0;
	pid = fork();
	if (pid == 0)
		child_process_prep(n, cmdv->content, (int [2]){input_fd, output_fd}, pipe_fd);
	else
	{ // Parent process
		if (n > 1)
		{
			close(pipe_fd[1]); // Close write end of the pipe
			execute_commands(n - 1, cmdv->next, pipe_fd[0], output_fd); // Recur for next command
			close(pipe_fd[0]); // Close read end after recursion
		}
		close(input_fd); // Close input in parent
		waitpid(pid, &status, 0); // Wait for the child process
	}
	return (status);
}

void	cleanup(int fds[2], t_list *lst)
{
	close(fds[0]);
	close(fds[1]);
	ft_lstclear(&lst, (void (*)(void *))ft_deletesplit);
}

int	main(int argc, char **argv)
{
	int		err;
	int		fds[2];
	t_list	*cmdv;

	if (argc < 5)
	{
		ft_putendl_fd(PUSAGE, STDERR_FILENO);
		return (1);
	}
	err = 0; 
	// validate output file / create.
	// validate input file.
	fds[0] = validate_inputfile(argv[1], &err);
	fds[1] = validate_outputfile(argv[argc - 1], &err);
	// validate all commands and create stack.
	cmdv = enqueue_cmds(argc, argv, &err);
	// if error at all, free everything and print the errors.
	if (!err)
		err = execute_commands(argc - 3, cmdv, fds[0], fds[1]);
	cleanup(fds, cmdv);
	return (err);
}
