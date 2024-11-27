/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:33:20 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/28 19:01:12 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 10

# endif

# ifndef MAX_FD

#  define MAX_FD 1024

# endif

typedef struct s_gnlbuffer
{
	char	*exit;
	char	*swap;
	int		eof;
	char	*buff;
}	t_gnlbuffer;

char	*get_next_line(int fd);

char	*fancy_str_join( char *s1, char *s2, int flag);

void	*zeroit(void *ptr, size_t size);

#endif
