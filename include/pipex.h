/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:58:48 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/20 16:33:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define PUSAGE "Usage:\n ./pipex infile cmd1 cmd2 outfile"

typedef enum e_err
{
	INPUTFILEERR = (1 << 0),
	OUTPUTFILEERR = (1 << 1),
	CMDNOTFOUND = (1 << 2),
}	t_err;

typedef char	**t_cmddesc;
//	char	**commandwithargs;


// cmd prep
int		check_cmdpath(char *cmd);
char	**get_path(void);
char	*get_cmdpath(char *cmd);

// queue
t_list	*enqueue_cmds(int argc, char **argv, int *err);
t_list	*ft_lstpop(t_list **lst);

// utils
void	ft_deletesplit(char **splt);

// file validation
int	validate_outputfile(char *path, int *error, int flag);
int	validate_inputfile(char *path, int *error);

int	setup_heredoc(char *endstr, int *io_fds);

int		exit_clause(int err);
void	cleanup(int fds[2], t_list *lst);

#endif