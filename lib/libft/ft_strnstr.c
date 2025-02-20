/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:09:55 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

// Big / Little naming convention is horrible:
// Reminder: little is the substring being searched for in big
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char		*lil_i;
	size_t			offset;

	if (!big
		|| !little
		|| len < ft_strlen(little)
		|| ft_strlen(little) > ft_strlen(big)
	)
		return (0);
	offset = 0;
	lil_i = little;
	while (*lil_i && *lil_i == *(big + offset))
	{
		offset++;
		lil_i++;
	}
	if (!*lil_i)
		return ((char *)big);
	else
		return (ft_strnstr(big + 1, little, len - 1));
}
