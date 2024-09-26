/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:24:09 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 15:28:20 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main ()
{
	char *x;
	x = malloc(2);
	x[1] = '\0';

	int pid = fork();
	if (pid) // main process
	{
		free(x);
	}
	else // child
	{
		char *p[2] = {"/home/hbreeze/.zshrc", 0};
		execve("/usr/bin/cat", p, __environ);
	}
	return (0);
}