/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_factory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:20:00 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:25 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <unistd.h>

static int	check_signed_value(void *value)
{
	if (!value)
		return (0);
	else if (*((int *)value) < 0)
		return (1);
	else
		return (0);
}

t_conv	*generate_conversion(char *str, void *value)
{
	t_conv	*output;

	if (!str)
		return (0);
	output = zeroit(malloc(sizeof(t_conv)), sizeof(t_conv));
	output->flags = non_f;
	output->control = str;
	output->value = value;
	output->type = str[ft_strlen(str)-1];
	if (output->type == 'd' || output->type == 'i')
		output->is_negative = check_signed_value(value);
	return (output);
}

void	delete_conversion(t_conv *c)
{
	if (!c)
		return ;
	if (ft_strchr("dixXcu", c->type))
		free(c->value);
	if (c->control)
		free(c->control);
	if (c->output)
		free(c->output);
	if (c->prefix)
		free(c->prefix);
	free(c);
	return ;
}

size_t	printed_length(t_conv *c)
{
	return (
		ft_strlen(c->prefix)
		+ ft_strlen(c->output)
		+ (1
			* (c->type == 'c'
				&& *(char *)c->value == '\0'
			)
		)
	);
}

void	print_conversion(t_conv *c)
{
	ft_putstr_fd(c->prefix, 1);
	write(1, "\0", 1 * (c->type == 'c' && *((char *)c->value) == '\0'));
	ft_putstr_fd(c->output, 1);
}
