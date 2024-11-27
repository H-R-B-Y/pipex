/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:59:41 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/30 13:07:29 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	digits_needed(long long n)
{
	long	digits;
	int		i;

	digits = 1;
	i = 0;
	while (digits <= n)
	{
		digits *= 10;
		i++;
	}
	return ((unsigned int)(i + !(n)));
}

char	*ft_itoa(int n)
{
	size_t			digits;
	char			*output;
	int				is_signed;
	long			num;

	is_signed = 0;
	num = n;
	if (n < 0 && ++is_signed)
		num *= -1;
	digits = digits_needed(num) + is_signed;
	output = malloc(digits + 1);
	if (!output)
		return (0);
	output[digits--] = '\0';
	if (is_signed)
		output[0] = '-';
	while (num / 10 > 0)
	{
		output[digits] = (num % 10) + '0';
		num /= 10;
		digits--;
	}
	output[digits] = (num % 10) + '0';
	return (output);
}
