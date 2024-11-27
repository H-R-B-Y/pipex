/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:38:24 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/05 12:03:47 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char		*s1_i;
	const char		*s2_i;
	size_t			index;

	s1_i = s1;
	s2_i = s2;
	index = 0;
	if (!(n))
		return (0);
	while (index + 1 < n
		&& *s1_i
		&& *s2_i
		&& (*s1_i == *s2_i)
	)
	{
		s1_i++;
		s2_i++;
		index++;
	}
	return ((unsigned char)*s1_i - (unsigned char)*s2_i);
}
