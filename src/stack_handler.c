/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:20 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/28 12:36:34 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_cmd_err(char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

t_cmddesc	get_validcmd(char *cmd)
{
	t_cmddesc	cmdsplt;
	char		*realpath;

	if (!cmd)
		return (0);
	cmdsplt = ft_split(cmd, ' ');
	if (!cmdsplt)
		return (0);
	realpath = ft_strdup(cmdsplt[0]);
	if (!(realpath[0] == '.' || realpath[0] == '/'))
		realpath = get_cmdpath(realpath);
	if (!realpath || !check_cmdpath(realpath))
	{
		ft_deletesplit(cmdsplt);
		free(realpath);
		return (0);
	}
	free(cmdsplt[0]);
	cmdsplt[0] = realpath;
	return (cmdsplt);
}

int	push_validcmd(t_list **lst, char *cmd)
{
	t_cmddesc	cmdsplt;
	t_list		*item;

	if (!cmd)
		return (0);
	cmdsplt = get_validcmd(cmd);
	if (!cmdsplt)
		return (0);
	item = ft_lstnew(cmdsplt);
	if (!item)
		return (0);
	ft_lstadd_front(lst, item);
	return (1);
}

t_list	*enqueue_cmds(int argc, char **argv, int *err)
{
	int		iter;
	t_list	*output;
	int		code;

	iter = argc;
	iter -= 4;
 	argv += 2;
	output = 0;
	while (iter >= 0)
	{
		code = push_validcmd(&output, argv[iter]);
		if (!code)
		{
			*err |= CMDNOTFOUND;
			print_cmd_err(argv[iter]);
		}
		iter--;
	}
	return (output);
}
