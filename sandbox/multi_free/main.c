/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:40:38 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 14:53:10 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char *c;
	c = malloc(2);
	c[0] = 'h';
	c[1] = '\0';

	int pid = fork();
	if (pid)
	{
		free(c);
	}
	return (0);
}

// Theory:
// Result: