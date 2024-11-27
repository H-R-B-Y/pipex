/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:14:42 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/05 12:08:35 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	word_count(const char *str, char sep)
{
	size_t			count;
	int				last_sep;
	int				index;

	count = 0;
	last_sep = -1;
	index = 0;
	if (!str)
		return (0);
	while (str[index] != '\0')
	{
		if (str[index] == sep)
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

static size_t	word_len(const char *str, char sep)
{
	char	*index;

	index = (char *)str;
	while (*index != '\0' && *index != sep)
		index++;
	return (index - str);
}

char	**ft_split(char const *s, char c)
{
	size_t			word_index;
	char			**output;
	int				word_started;

	word_index = 0;
	word_started = 1;
	if (!s)
		return (0);
	output = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!output)
		return (0);
	output[word_count(s, c)] = 0;
	while (*s)
	{
		if (*s == c)
			word_started = 1;
		else if (*s != c && word_started && word_started--)
			output[word_index++] = ft_substr(s, 0, word_len(s, c));
		s++;
	}
	return (output);
}
