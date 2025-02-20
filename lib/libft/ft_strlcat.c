/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:33:35 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:37:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char			*dest_i;
	size_t			dest_len;
	size_t			src_len;

	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	dest_i = &(dest[dest_len]);
	if (size <= dest_len)
		return (src_len + size);
	while (*src && ((dest_i - dest) - dest_len) < (size - dest_len) - 1)
		*dest_i++ = *src++;
	*dest_i = '\0';
	return (src_len + dest_len);
}
