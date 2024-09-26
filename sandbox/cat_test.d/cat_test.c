/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:16:04 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/25 17:38:01 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main ()
{
	char *f1 = "a.txt";
	char *f2 = "b.txt";
	int	p[2];
	int fd1 = open(f1, O_RDONLY);
	int fd2 = open(f2, O_WRONLY | O_CREAT, 0777);

	char t[1];
	t[0] = '\n';
	if (pipe(p))
		perror(0);
	dup2(p[1], 1);
	while (read(fd1, t, 1))
		write(1, t, 1);
	write(1, "\0", 1);
	while (read(p[0], t, 1) && t[0] != '\0')
		write(fd2, t, 1 * t[0] != '\0');
	close(fd1);
	close(fd2);
	close(p[0]);
	close(p[1]);
}