/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:38:52 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/25 18:01:53 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int pid;

	pid = fork();
	if (pid)
	{
		sleep(5);
		printf("Secondary execution. PID: %d\n", pid);
	}
	else
	{
		printf("Primary execution.\n");
	}
	return (0);
}