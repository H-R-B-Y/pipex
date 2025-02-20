/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:42:27 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

t_conv	*truncate_precision(t_conv *c)
{
	char	*tmp;

	if (!c || !c->output)
		return (0);
	tmp = c->output;
	if (!c->value && c->precision > 6)
		return (c);
	if (!c->value && c->precision < 6)
		return (free(tmp), c->output = ft_strdup(""), c);
	c->output = ft_substr(c->output, 0, c->precision);
	if (!c->output)
		c->output = ft_strdup("");
	free(tmp);
	return (c);
}

t_conv	*prepend_precision(t_conv *c)
{
	size_t	pad_count;
	char	*padding;

	if (!c || !c->output || !test_flag(c->flags, dot_f))
		return (0);
	if (c->precision == 0 && ft_strchr("xXdui", c->type) && *c->output == '0')
		return (free(c->output), c->output = ft_strdup(""), c);
	if ((ft_strlen(c->output) >= c->precision && c->type != 's')
		|| (!c->value && 'p' == c->type)
		|| (c->type == 's' && ft_strlen(c->output) < c->precision))
		return (c);
	if (c->type == 's' && ft_strlen(c->output) > c->precision)
		return (truncate_precision(c));
	pad_count = c->precision - ft_strlen(c->output);
	padding = malloc(pad_count + 1);
	padding[pad_count] = '\0';
	ft_memset(padding, '0', pad_count);
	c->output = str_join_and_free(padding, c->output, (1 << 1) | (1 << 2));
	return (c);
}
