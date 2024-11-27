/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:24:59 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/31 15:53:42 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	if (!src)
		return (0);
	if (!dest)
		return (0);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (src < dest)
		while (n--)
			temp_dest[n] = temp_src[n];
	return (dest);
}
