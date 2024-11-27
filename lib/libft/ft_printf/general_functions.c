/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 01:43:04 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/25 12:15:57 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_upper_wrapper(unsigned int x, char *c)
{
	(void)x;
	*c = ft_toupper(*c);
}

void	*zeroit(void *ptr, size_t n)
{
	size_t	index;

	if (!ptr)
		return (0);
	index = 0;
	while (index < n)
		((unsigned char *) ptr)[index++] = (unsigned char ) '\0';
	return (ptr);
}

char	*str_join_and_free(char *s1, char *s2, unsigned int flag)
{
	char	*output;
	size_t	size1;
	size_t	size2;
	size_t	index;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	index = 0;
	output = 0;
	if (size1 + size2 + 1 != 1)
		output = zeroit(malloc(size1 + size2 + 1), (size1 + size2 + 1));
	while (output && s1 && index < size1)
		output[index++] = (char)*s1++;
	index = 0;
	while (output && s2 && index < size2)
		output[size1 + index++] = (char)*s2++;
	if ((flag & (1 << 1)) == (1 << 1))
		free(s1 - size1);
	if ((flag & (1 << 2)) == (1 << 2))
		free(s2 - index);
	return (output);
}

char	*create_padding(t_conv *c)
{
	char	*padding;
	size_t	pad_count;

	pad_count = c->min_width - (ft_strlen(c->output) + ft_strlen(c->prefix));
	pad_count -= (c->type == 'c' && *(char *)c->value == '\0');
	if (!pad_count)
		return (ft_strdup(""));
	padding = malloc(pad_count + 1);
	if (!padding)
		return (ft_strdup(""));
	padding[pad_count] = '\0';
	if (test_flag(c->flags, zro_f) && !test_flag(c->flags, min_f))
		ft_memset(padding, '0', pad_count);
	else
		ft_memset(padding, ' ', pad_count);
	return (padding);
}

void	substr_atoi(char *str, size_t *value)
{
	char	*end;

	if (!str || !value)
		return ;
	if (!ft_isdigit(*str))
		return ;
	end = str;
	while (*end && ft_isdigit(*end))
		end++;
	end = ft_substr(str, 0, end - str);
	*value = (size_t)atoi(end);
	free(end);
}
