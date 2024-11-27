/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-25 15:12:11 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-25 15:12:11 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_deletesplit(char **splt)
{
	int	index;

	index = 0;
	while(splt && splt[index])
		free(splt[index++]);
	free(splt);
}
