/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 19:28:16 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/05 11:56:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*start;

	start = (char *)s;
	while (*s)
		s++;
	while (start < s && (unsigned char)*s != (unsigned char)c)
		s--;
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
