/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitfn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:11:34 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"
#include <stdlib.h>

static size_t	wordcntfn(const char *str, int (*delim)(int c))
{
	size_t			count;
	int				last_sep;
	int				index;

	count = 0;
	last_sep = -1;
	index = 0;
	if (!str || !delim)
		return (0);
	while (str[index] != '\0')
	{
		if (delim(str[index]))
		{
			if (index - last_sep > 1)
				count++;
			last_sep = index;
		}
		index++;
	}
	if (index - last_sep > 1)
		count += 1;
	return (count);
}

static size_t	wordlenfn(const char *str, int (*delim)(int c))
{
	char	*index;

	if (!str || !delim)
		return (0);
	index = (char *)str;
	while (*index != '\0' && !delim(*index))
		index++;
	return (index - str);
}

char	**ft_splitfn(char const *s, int (*delim)(int c))
{
	size_t			word_index;
	char			**output;
	int				word_started;

	word_index = 0;
	word_started = 1;
	if (!s || !delim)
		return (0);
	output = malloc((wordcntfn(s, delim) + 1) * sizeof(char *));
	if (!output)
		return (0);
	output[wordcntfn(s, delim)] = 0;
	while (*s)
	{
		if (delim(*s))
			word_started = 1;
		else if (!delim(*s) && word_started && word_started--)
			output[word_index++] = ft_substr(s, 0, wordlenfn(s, delim));
		s++;
	}
	return (output);
}
