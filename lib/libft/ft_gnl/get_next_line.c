/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:33:59 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	read_file(int fd, t_gnlbuffer *m)
{
	int	bytes;

	m->buff = malloc(BUFFER_SIZE + 1);
	if (!m->buff)
		return (-1);
	while (!ft_strchr(m->exit, '\n') && !m->eof)
	{
		bytes = read(fd, m->buff, BUFFER_SIZE);
		if (bytes < 0 && ((m->exit && (free(m->exit), 1)) || 1))
			return (free(m->buff), (m->exit = 0), 0);
		m->eof += 1 * (bytes == 0);
		m->buff[bytes] = '\0';
		m->exit = (fancy_str_join(m->exit, m->buff, 1));
	}
	free(m->buff);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnlbuffer	m[MAX_FD];
	int					bytes;
	char				*tmp;

	if (fd < 0 || fd >= MAX_FD)
		return ((char *)0ul);
	bytes = read_file(fd, &(m[fd]));
	if (bytes < 0)
		return (0);
	if (m[fd].eof && m[fd].exit && !ft_strchr(m[fd].exit, '\n'))
		return (tmp = fancy_str_join(m[fd].exit, 0, 1), m[fd].exit = 0, tmp);
	else if (m[fd].exit)
	{
		m[fd].swap = fancy_str_join((ft_strchr(m[fd].exit, '\n') + 1), 0, 0);
		tmp = ft_substr(m[fd].exit, 0,
				(ft_strchr(m[fd].exit, '\n') - m[fd].exit) + 1);
		return (free(m[fd].exit), m[fd].exit = m[fd].swap, m[fd].swap = 0, tmp);
	}
	return (m[fd].eof = 0, (char *)0ul);
}
