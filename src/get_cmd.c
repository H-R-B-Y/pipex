/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:22 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/28 12:29:51 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

extern char	**environ;

/*
For use when a path is supplied
*/
int	check_cmdpath(char *cmd)
{
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

/*
Will return the split paths from environ.
ft_split like:
[0] /usr/bin
[1] /usr/share/bin
etc, etc 
*/
char	**get_path(void)
{
	char	**envpaths;

	envpaths = 0;
	while (environ && *environ)
	{
		if ((**environ != 'P' || ft_strncmp("PATH=", *environ, 5)) && ++environ)
			continue ;
		envpaths = ft_split(ft_strchr(*environ, '=') + 1, ':');
		break ;
	}
	if (!envpaths)
		return (0);
	return (envpaths);
}

/*
Only use if not already a path.
0 means there was an error.
Dont include args!!!!
*/
char	*get_cmdpath(char *cmd)
{
	char	**paths;
	char	*tmp;
	int		index;

	paths = get_path();
	index = 0;
	tmp = ft_strjoin("/", cmd);
	free(cmd);
	cmd = tmp;
	if (!cmd)
		return ((void *)0);
	while (paths && paths[index])
	{
		tmp = ft_strjoin(paths[index], cmd);
		if (check_cmdpath(tmp))
			break ;
		free(tmp);
		tmp = 0;
		index++;
	}
	free(cmd);
	ft_deletesplit(paths);
	return (tmp);
}
