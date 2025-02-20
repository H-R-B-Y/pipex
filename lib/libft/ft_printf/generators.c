/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:15:32 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	char_and_string(t_conv *c)
{
	if (c->type == 'c')
	{
		c->output = malloc(2);
		c->output[1] = '\0';
		c->output[0] = *(char *)(c->value);
	}
	else if (c->type == 's')
	{
		c->output = ft_strdup(c->value);
		if (!c->output)
			c->output = ft_strdup("(null)");
	}
}

void	numerics(t_conv *c)
{
	if (c->type == 'd' || c->type == 'i')
		c->output = int_to_str(c->value);
	else if (c->type == 'x' || c->type == 'X')
		c->output = uint_to_hex((unsigned *)c->value);
	else if (c->type == 'u')
		c->output = uint_to_str((unsigned *)c->value);
}

t_conv	*generate_output(t_conv *c)
{
	if (!c)
		return (0);
	else if (ft_strchr("dixXu", c->type))
		numerics(c);
	else if (c->type == 'c' || c->type == 's')
		char_and_string(c);
	else if (c->type == 'p')
		c->output = ptr_to_hex(c->value);
	else if (c->type == '%')
		c->output = ft_strdup("%");
	if (c->type != 'c' && c->type != '%')
		prepend_precision(c);
	if (c->type == 'X')
		ft_striteri(c->output, &to_upper_wrapper);
	return (c);
}
