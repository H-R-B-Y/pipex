/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:50:51 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/31 12:48:33 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*output;
	size_t			size;

	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	output = malloc(size + 1);
	if (!output)
		return (0);
	output[size] = '\0';
	ft_memmove(output, s1, ft_strlen(s1));
	ft_memmove(output + ft_strlen(s1), s2, ft_strlen(s2));
	return (output);
}
