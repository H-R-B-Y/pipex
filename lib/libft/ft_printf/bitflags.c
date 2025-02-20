/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:05:49 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	set_flag(unsigned int *flags, t_escflags flag)
{
	*flags |= flag;
}

void	unset_flag(unsigned int *flags, t_escflags flag)
// this funtion does this...
// flip bits to create bit mask, then and operate to unset
{
	*flags &= ~(int)flag;
}

// if the and operator is equal to the test flag returns 1
int	test_flag(unsigned int flags, t_escflags flag)
{
	return ((flags & flag) == flag);
}

t_conv	*set_conversion_flags(t_conv *c)
{
	char	*str_i;

	if (!c || !(c->control))
		return (0);
	str_i = c->control;
	while (*str_i && ft_strchr("+ -0'#", *str_i))
	{
		c->flags |= add_f * (*str_i == '+');
		c->flags |= spc_f * (*str_i == ' ');
		c->flags |= min_f * (*str_i == '-');
		c->flags |= zro_f * (*str_i == '0');
		c->flags |= qot_f * (*str_i == '\'');
		c->flags |= hsh_f * (*str_i == '#');
		str_i++;
	}
	return (c);
}

t_conv	*correct_flags(t_conv *c)
{
	if (!c)
		return (0);
	if (test_flag(c->flags, zro_f) && test_flag(c->flags, dot_f))
		unset_flag(&c->flags, zro_f);
	if (test_flag(c->flags, add_f) && test_flag(c->flags, spc_f))
		unset_flag(&c->flags, spc_f);
	if (test_flag(c->flags, zro_f) && test_flag(c->flags, min_f))
		unset_flag(&c->flags, zro_f);
	if (!c->min_width)
		unset_flag(&c->flags, zro_f);
	return (c);
}
