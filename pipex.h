/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:27:32 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 14:13:26 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
/*
Usage:
ft_split
- Split the envp.
ft_strchr
- Create a pointer to the first '=' sign in envp
*/

# include <unistd.h>
/*
*/

# include <stdlib.h>
/*
*/

# include <fcntl.h>
/*
*/

# include <stdio.h>
/*
*/

# include <sys/wait.h>
/*
*/


void	cleanup(char **envpaths);
char	**get_path(char **envp);


#endif