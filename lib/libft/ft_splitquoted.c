/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:26:18 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"
#include <stdlib.h>

	// int				index of last sep;
	// int				index;
	// int				quoted;
static size_t	qtwordcnt(const char *str, int (*delim)(int c))
{
	size_t			count;
	int				indexes[3];

	indexes[0] = -1;
	ft_memset(&indexes[1], '\0', sizeof(int) * 2);
	count = 0;
	if (!str || !delim)
		return (0);
	while (str[indexes[1]] != '\0')
	{
		if (str[indexes[1]] == '"')
			indexes[2] = !indexes[2];
		if (!indexes[2] && delim(str[indexes[1]]))
		{
			if (indexes[1] - indexes[0] > 1)
				count++;
			indexes[0] = indexes[1];
		}
		indexes[1]++;
	}
	if (indexes[1] - indexes[0] > 1)
		count += 1;
	return (count);
}

static size_t	qtwordlen(const char *str, int (*delim)(int c), int quoted)
{
	char	*index;

	index = (char *)str;
	while (*index != '\0' && ((!delim(*index) && !quoted) || quoted))
	{
		index++;
		if (*index == '"' && quoted && ++index)
			break ;
	}
	return (index - str);
}

char	**ft_splitquoted(const char *str, int (*delim)(int c))
{
	size_t			index;
	char			**output;
	int				isword;
	int				quote;

	index = 0;
	isword = 1;
	quote = 0;
	if (!str || !delim)
		return (0);
	output = malloc((qtwordcnt(str, delim) + 1) * sizeof(char *));
	if (output)
		output[qtwordcnt(str, delim)] = 0;
	while (output && *str)
	{
		if (*str == '"')
			quote = !quote;
		if (!quote && delim(*str))
			isword = 1;
		else if (!delim(*str) && isword && isword--)
			output[index++] = ft_substr(str, 0, qtwordlen(str, delim, quote));
		str++;
	}
	return (output);
}
