/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 20:29:30 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_conv	*set_padding(t_conv *c)
{
	char	*padding;
	char	*result;

	if (!c || !c->min_width
		|| ft_strlen(c->output) + ft_strlen(c->prefix) >= c->min_width
		|| (c->type == 'c' && *(char *)c->value == '\0' && c->min_width < 1))
		return (c);
	padding = create_padding(c);
	if (test_flag(c->flags, min_f))
		result = str_join_and_free(c->output, padding, 6);
	else if (test_flag(c->flags, zro_f))
		result = str_join_and_free(padding, c->output, 6);
	else
	{
		result = str_join_and_free(padding, c->prefix, 6);
		return (c->prefix = result, c);
	}
	return (c->output = result, c);
}

t_conv	*set_prefix(t_conv *c)
{
	c->prefix = ft_strdup("");
	if (c->value == 0)
		return (c);
	if ((((c->type == 'x' || c->type == 'X')
				&& test_flag(c->flags, hsh_f))
			&& *((int *)c->value) != 0)
		|| c->type == 'p')
		c->prefix = str_join_and_free(c->prefix, "0x", 2);
	if (c->type == 'X')
		ft_striteri(c->prefix, &to_upper_wrapper);
	if (!ft_strchr("dixXp", c->type))
		return (c);
	if (c->is_negative)
		c->prefix = str_join_and_free(c->prefix, "-", 2);
	else if (test_flag(c->flags, add_f) && !test_flag(c->flags, spc_f))
		c->prefix = str_join_and_free(c->prefix, "+", (1 << 1));
	else if (test_flag(c->flags, spc_f))
		c->prefix = str_join_and_free(c->prefix, " ", 2);
	return (c);
}
