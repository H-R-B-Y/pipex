/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:38:10 by hbreeze           #+#    #+#             */
/*   Updated: 2025/03/07 15:01:05 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

extern char	**environ;

/*
Stupid naming scheme needs to be changed cause this is so confusing.abort
	io_fd[0] is EITHER the read end of the pipe from the previous command
			OR the input file / here_doc.
	io_fd[1] is the OUTPUT file in either TRUNC or APPEND mode.
	pipe is the pipe that the process writes it's output too!
for commands n > 1:
	dupe the pipe to STDOUT so output is written into pipe.
	close local fds for pipe.
for command n == 1
	dupe output file in either TRUNC or APPEND mode to \
		STDOUT to write to the output file.
Redirect the reading end of the io_pipe to stdin so \
	executed command reads from pipe/file.
Then execute the command in cmd!
*/
void	child_process_prep(int n[2], t_list *cmdv, int io_fd[2], int pipe[2])
{
	t_cmddesc	cmd;

	cmd = ft_lstget(cmdv, n[1])->content;
	if (n[0] - n[1] > 1)
	{
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[0]);
		close(pipe[1]);
	}
	else
		dup2(io_fd[1], STDOUT_FILENO);
	dup2(io_fd[0], STDIN_FILENO);
	close(io_fd[0]);
	close(io_fd[1]);
	if (execve(cmd[0], &cmd[0], environ) < 0)
		cleanup(0, 0, cmdv, "execve");
}

/*
Bit of a confusing one this XD

We start from the first command in the list:
<input_file cowsay | wc -l | cat | output_file
             ^-this one!
where n would be 3.
The main process creates a pipe
the main process forks
	The child process executes cowsay reading from the inputfd \
		and outputing to the pipe
the main process closes the write end of the pipe, and recurs \
	passing the pipe read end as the new input_fd.

	the next recursion points to "wc -l"
	creates a new pipe
	forks
		the child process executes "wc -l" reading from the last pipe \
			and writing to the new pipe
	the main process then closes the writing end of the pipe \
		and recurs passing the new pipe along.
		.... etc, etc,
	the main process then awaits the returned status code \
		of the spawned child process.
	and returns it.
The final command then returns it retcode all the way back to the \
	bottom of the recursion stack.
and this ret code is returned to the main function to act as the retcode for
pipex.out
*/
// io_fd [0] input
// io_fd [1] output
int	execute_commands(int n[2], t_list *cmdv, int io_fd[2])
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (n[0] - n[1] > 1 && pipe(pipe_fd) < 0)
		cleanup(io_fd, (void *)0, cmdv, "pipe");
	status = 0;
	pid = fork();
	if (pid < 0)
		cleanup(io_fd, pipe_fd, cmdv, "fork");
	else if (pid == 0)
		child_process_prep(n, cmdv, io_fd, pipe_fd);
	else
	{
		if (n[0] - n[1] > 1)
		{
			close(pipe_fd[1]);
			status = execute_commands((int [2]){n[0], n[1] + 1},
					cmdv, (int [2]){pipe_fd[0], io_fd[1]});
		}
		else
			waitpid(pid, &status, 0);
		close(io_fd[0]);
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
	{
		err = execute_commands((int [2]){argc - 3, 0}, cmdv, fds);
		cleanup((int [2]){0, fds[1]}, (void *)0, cmdv, (void *)0);
		if (err)
			err = WEXITSTATUS(err);
		return (err);
	}
	cleanup(fds, (void *)0, cmdv, (void *)0);
	return (1);
}
