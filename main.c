/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:09:01 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 21:03:46 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_pipe(int argc, char **argv, int *my_pipe, int *last_pipe)
{
	int fd;

	if (!my_pipe || !last_pipe)
		return (1);
	close(last_pipe[1]);
	dup2(last_pipe[0], STDIN_FILENO);
	if (argc == 2)
	{
		if (access(argv[1], F_OK) != 0)
			fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
		else
			fd = open(argv[1], O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		return (0);
	}
	pipe(my_pipe);
	dup2(my_pipe[1], STDOUT_FILENO);
	return (0);
}

// // TEST FOR INIT_PIPE
// int main ()
// {
// 	// Create two temporary file descriptors.
// 	int tmp[2];
// 	tmp[0] = open("./main.c", O_RDONLY);
// 	tmp[1] = open("./Makefile", O_RDONLY);

// 	// Create a new pipe.
// 	int pip[2];

// 	// Initialise a dummy argv (2 commands and 1 output file)
// 	char *argvvvv[] = {"test", "test", "./output_test_initpipe"};
	
// 	// Init a pipe at argc == 3
// 	// 	This will close tmp[1] (writing end)
// 	// 	duplicate tmp[0] (reading end) into STDIN
// 	// 	create a new pipe (pip)
// 	// 	and duplicate pip[1] (writing end) into the STDOUT
// 	init_pipe(3, argvvvv, pip, tmp);
// 	int pip2[2];

// 	// Init a pipe at argc == 2
// 	// 	Will close pip[1] (writing end)
// 	// 	Duplucate pip[0] (reading end) into STDIN
// 	// 	Then open a new fd (create a file) from argv[1]
// 	// 	Then duplicate the fd into STDOUT
// 	init_pipe(2, &(argvvvv[1]), pip2, pip);
// 	char *temp2[] = {0};
	
// 	// Because nothing is written into pip[1]
// 	// Nothing is written to the file
// 	execve("/usr/bin/cat", temp2, __environ);
// }

char	**get_path(char **envp)
{
	char **envpaths;
	
	envpaths = 0;
	while (envp && *envp)
	{
		if ((**envp != 'P' || ft_strncmp("PATH", *envp, 4)) && ++envp)
			continue ;
		envpaths = ft_split(ft_strchr(*envp, '=') + 1, ':');
		break ;
	}
	if (!envpaths)
		return (0);
	return (envpaths);
}

/*
WARN: this needs to be better protected.
*/
char	**prepare_cmd(char **argv)
{
	char **commands;
	char **paths;
	char **path_head;
	char *cmd;
	
	paths = get_path(__environ);
	commands = ft_split(*argv, ' ');
	path_head = paths;
	if (!paths || !commands)
		return (0);
	if ((**commands == '.' || **commands == '/')
		&& !access(*commands, F_OK) && !access(*commands, X_OK))
		return (commands);
	while(paths && *paths)
	{
		cmd = ft_strjoin(*paths, ft_strjoin("/", commands[0]));
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (free(commands[0]), commands[0] = cmd, commands);
		free(cmd), free(*paths++);
	}
	free(path_head);
	return (0);
}

// // TEST MAIN FOR ABOVE FUNCTION.
// int main ()
// {
// 	char **args;
// 	// ARGV will be passed to prepare cmd.
// 	// DUMMY ARGV containing cat command.
// 	char *cmd1[] = {"cat", 0};

// 	// Prepare command searches path for cat binary.
// 	// Returning string array startign with path for cat binary.
// 	args = prepare_cmd(cmd1);
// 	printf("%s %s\n", args[0], args[1]);

// 	// DUMMY ARGV containing a command and it's flag
// 	char *cmd2[] = {"cat -A", 0};
// 	// Prepare command searches path for binary.
// 	// Returning a string array with cat binary path,
// 	// followed by its flag.
// 	args = prepare_cmd(cmd2);
// 	printf("%s %s %s\n", args[0], args[1], args[2]);
// }

void	generalised_child_function(int argc, char **argv, int *last_pipe)
{
	int my_pipe[2];
	int pid;
	char **cmd;

	if (init_pipe(argc, argv, my_pipe, last_pipe))
		(close(my_pipe[0]), close(my_pipe[0]), exit(1));
	cmd = prepare_cmd(argv);
	if (!cmd)
		(ft_putstr_fd("Command not found!", 1), exit(1));
	if (argc > 2)
		pid = fork();
	else
		pid = 1;
	if (pid)
		(close(my_pipe[0]), execve(cmd[0], cmd + 1, __environ));
	else if (argc > 2)
		generalised_child_function(argc - 1, argv + 1, my_pipe);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		return (1);
	int pid;
	int my_pipe[2];
	int fd;
	char **cmd;

	pipe(my_pipe);
	pid = fork();
	if (!pid) // main process
	{
		close(my_pipe[0]);
		fd = open(argv[1], O_RDONLY);
		if (!fd)
			perror("FUCKING FAILED TO OPEN THE FILE!");
		dup2(fd, STDIN_FILENO);
		dup2(my_pipe[1], STDOUT_FILENO);
		cmd = prepare_cmd(&(argv[2]));
		execve(cmd[0], &(cmd[1]), __environ);
	}
	else
	{
		generalised_child_function(argc-3, &(argv[3]), my_pipe);
	}
}
