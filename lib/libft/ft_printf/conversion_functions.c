/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:36:06 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*int_to_str(int *v)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(*v);
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 1);
		free(str);
		str = tmp;
	}
	return (str);
}

static size_t	digits_needed(unsigned long n, int base)
{
	size_t	i;

	i = 1;
	while (n / base > 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

char	*uint_to_str(unsigned int *v)
{
	char			*str;
	size_t			digits;
	unsigned int	num;

	if (!v)
		return (ft_strdup(""));
	num = *v;
	digits = digits_needed(num, 10);
	str = malloc(digits + 1);
	str[digits] = '\0';
	if (!str)
		return (0);
	while (digits)
	{
		str[--digits] = '0' + (num % 10);
		num /= 10;
	}
	return (str);
}

char	*uint_to_hex(unsigned int *v)
{
	char			*output;
	unsigned long	num;
	size_t			digits;

	num = (unsigned long)*v;
	digits = digits_needed(num, 16);
	output = malloc(digits + 1);
	if (!output)
		return (0);
	output[digits--] = '\0';
	while (num / 16 > 0)
	{
		output[digits] = "0123456789abcdef"[num % 16];
		num /= 16;
		digits--;
	}
	output[digits] = "0123456789abcdef"[num % 16];
	return (output);
}

char	*ptr_to_hex(void *ptr)
{
	unsigned long	p;
	size_t			digits;
	char			*output;

	if (!ptr)
		return (ft_strdup("(nil)"));
	p = (unsigned long)ptr;
	digits = digits_needed(p, 16);
	output = malloc(digits + 1);
	if (!output)
		return (0);
	output[digits--] = '\0';
	while (p / 16 > 0)
	{
		output[digits] = "0123456789abcdef"[p % 16];
		p /= 16;
		digits--;
	}
	output[digits] = "0123456789abcdef"[p % 16];
	return (output);
}
