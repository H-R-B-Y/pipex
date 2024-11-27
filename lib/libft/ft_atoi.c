/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:40:30 by hbreeze           #+#    #+#             */
/*   Updated: 2024/08/31 15:35:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(char c)

{
	return (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r'
	);
}

int	ft_atoi(const char *nptr)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	if (*nptr == 0)
		return (0);
	while (is_whitespace(*nptr))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-' && nptr++)
		sign *= -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		output *= 10;
		output += *nptr - '0';
		nptr++;
	}
	return (output * sign);
}
