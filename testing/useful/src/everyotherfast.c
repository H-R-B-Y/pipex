/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everyotherfast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:47:52 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/26 19:50:19 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char t;
	unsigned long long i = 0;
	while(++i, read(0, &t, 1))
		ft_putchar_fd((i%2==0 )? ft_tolower(t) : ft_toupper(t), 1);
	return (0);
}