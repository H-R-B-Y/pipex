/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:21:07 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/05 12:07:18 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// WHO KEEPS SIGNING THESE CHARS T-T
char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s && (unsigned char)*s != (unsigned char)c)
		s++;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
