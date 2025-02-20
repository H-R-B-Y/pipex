/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/20 16:36:20 by hbreeze          ###   ########.fr       */
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

int	parse_flags(int *argc, char ***argv, int *io_fds, int *err)
{
	int	flag;

	if (!ft_strncmp((*argv)[1], "here_doc", 9))
		flag = 1;
	else if (!ft_strncmp((*argv)[1], "append_doc", 11))
		flag = 3;
	else if (!ft_strncmp((*argv)[1], "append_", 8))
		flag = 2;
	else
		flag = 0;
	(*argv) += 1 * (!!flag);
	(*argc) -= 1 * (!!flag);
	if (flag & 1)
		setup_heredoc((*argv)[1], io_fds);
	else
		io_fds[0] = validate_inputfile((*argv)[1], err);
	return (flag);
}

int	main(int argc, char **argv)
{
	int		err;
	int		fds[2];
	t_list	*cmdv;
	int		flag;

	if (argc < 5)
		return (exit_clause(1));
	err = 0;
	flag = parse_flags(&argc, &argv, fds, &err);
	fds[1] = validate_outputfile(argv[argc - 1], &err, flag);
	cmdv = enqueue_cmds(argc, argv, &err);
	if (!err)
		err = execute_commands(argc - 3, cmdv, fds[0], fds[1]);
	cleanup(fds, cmdv);
	return (err);
}
