/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tolowerfast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:47:52 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 15:50:59 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char t;
	while(read(0, &t, 1))
		ft_putchar_fd(ft_tolower(t), 1);
	return (0);
}