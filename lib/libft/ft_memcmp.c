/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:03:19 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/31 12:49:50 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_i;
	const unsigned char	*s2_i;
	size_t				index;

	s1_i = s1;
	s2_i = s2;
	index = 0;
	if (!n || !s1 || !s2)
		return (0);
	while (index + 1 < n && (*s1_i == *s2_i))
	{
		s1_i++;
		s2_i++;
		index++;
	}
	return (*s1_i - *s2_i);
}
