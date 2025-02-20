/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:40:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/20 16:40:42 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	validate_inputfile(char *path, int *error)
{
	int	fd;

	if (!path || !error)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*error |= INPUTFILEERR;
		perror(path);
	}
	return (fd);
}

int	validate_outputfile(char *path, int *error, int flag)
{
	int	fd;
	
	if (!path || !error)
		return (0);
	if (access(path, F_OK) == 0 && access(path, R_OK) != 0)
	{
		*error |= OUTPUTFILEERR;
		perror(path);
		return (0);
	}
	else if (access(path, F_OK) != 0)
		fd = open(path, O_WRONLY | O_CREAT
			| (O_APPEND * !!(flag & 2)), 0755);
	else
		fd = open(path, O_WRONLY
			| (O_APPEND * !!(flag & 2))
			| (O_TRUNC * !(flag & 2)));
	if (fd < 0)
	{
		*error |= OUTPUTFILEERR;
		perror(path);
	}
	return (fd);
	
}
