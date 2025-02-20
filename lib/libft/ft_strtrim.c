/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:06:22 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./include/libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t			size;
	char			*end;

	size = 0;
	end = (char *)s1;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (*end)
		end++;
	while (*(--end))
		if (!ft_strchr(set, *end))
			break ;
	size = (end - s1) + 1;
	return (ft_substr(s1, 0, size));
}
