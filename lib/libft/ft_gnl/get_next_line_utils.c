/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:47:00 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:55 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*fancy_str_join( char *s1, char *s2, int flag)
{
	char	*output;
	size_t	size1;
	size_t	size2;
	size_t	index;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	index = 0;
	if (!(size1 + size2))
		return (0);
	output = malloc(size1 + size2 + 1);
	if (!output)
		return (0);
	output[size1 + size2] = '\0';
	while (s1 && index < size1)
		output[index++] = (char)*s1++;
	index = 0;
	while (s2 && index < size2)
		output[size1 + index++] = (char)*s2++;
	if ((flag & (1 << 0)) == (1 << 0))
		free(s1 - size1);
	if ((flag & (1 << 1)) == (1 << 1))
		free(s2 - index);
	return (output);
}

void	*zeroit(void *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char *)ptr)[i++] = 0;
	return (ptr);
}
