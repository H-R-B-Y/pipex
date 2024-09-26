/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:24:29 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 17:00:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// For testing.
#include <stdio.h>

char	**get_path(char **envp)
{
	char **p;
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

void	cleanup(char **envpaths)
{
	char **p;

	if (!envpaths) 
		return ;
	p = envpaths;
	while (envpaths && *envpaths)
	{
		free(*envpaths);
		envpaths++;
	}
	free(p);
	return ;
}

void childProcess(char **envpaths, char *cmd, int p[2], char *file)
{
	char *arg[1] = {0};
	close(p[1]);
	int io_fd = open(file, O_WRONLY | O_CREAT, 0777);
	dup2(p[0], STDIN_FILENO);
	dup2(io_fd, STDOUT_FILENO);
	execve(cmd, arg, __environ);
}

// ENVP is null terminated.
int main(int argc, char **argv, char **envp)
{
	char **envpaths;
	int p[2];
	int pid;
	int io_fd;
	
	if (argc != 5)
		return (1);

	envpaths = get_path(envp);
	if (!envpaths)
		return (1);
	if (pipe(p))
		perror("ERR");
	
	pid = fork();
	if (!pid) // Child Process;
		childProcess(envpaths, argv[3], p, argv[4]);
	close(p[0]);
	io_fd = open(argv[1], O_RDONLY);
	dup2(io_fd, STDIN_FILENO);
	dup2(p[1], STDOUT_FILENO);
	char *arg[1] = {0};
	execve(argv[2], arg, __environ);
	return (0);
}