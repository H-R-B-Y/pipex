/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:25:06 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	*pop_escaped_str(char **str)
{
	char	*start;
	char	*duplicate;

	if (!str || !*str || **str != '%')
		return (0);
	start = *str;
	(*str)++;
	while (**str && ft_strchr("+ -0'#", **str))
		(*str)++;
	if (**str && ft_strchr("123456789", **str) && (*str)++)
		while (**str && ft_isdigit(**str))
			(*str)++;
	if (**str == '*')
		(*str)++;
	if (**str && **str == '.' && (*str)++)
		while (**str && ft_isdigit(**str))
			(*str)++;
	if (*((*str) - 1) == '.' && **str == '*')
		(*str)++;
	if (**str && !ft_strchr("cspdiuxX%", **str))
		return (0);
	duplicate = ft_substr(start, 1, (*str - start));
	return ((*str)++, duplicate);
}

t_conv	*parse_width(t_conv *c, va_list args)
{
	char	*start;

	if (!c || !c->control)
		return (0);
	start = c->control;
	while (*start && ft_strchr("+ -0'#", *start))
		start++;
	if (!ft_strchr("123456789", *start))
		return (c);
	if (*start != '*')
		substr_atoi(start, &c->min_width);
	else
		c->min_width = va_arg(args, int);
	set_flag(&c->flags, len_f);
	return (c);
}

t_conv	*parse_precision(t_conv *c, va_list args)
{
	char	*start;

	if (!c || !c->control || !ft_strchr(c->control, '.'))
		return (0);
	start = c->control;
	while (*start && ft_strchr("+ -0'#123456789", *start))
		start++;
	if (!*start || *start != '.')
		return (0);
	set_flag(&c->flags, dot_f);
	if (*(++start) != '*')
		substr_atoi(start, &c->precision);
	else
		c->precision = va_arg(args, int);
	return (c);
}

void	*malloc_arg(va_list args, char s)
{
	int		*int_result;
	char	*char_result;

	if (s == 'd' || s == 'i' || s == 'x' || s == 'X')
	{
		int_result = malloc(sizeof(int));
		*int_result = va_arg(args, int);
		return (int_result);
	}
	else if (s == 'c')
	{
		char_result = malloc(1);
		*char_result = va_arg(args, int);
		return (char_result);
	}
	else if (s == 'u')
	{
		int_result = malloc(sizeof(unsigned int));
		*int_result = va_arg(args, unsigned int);
		return (int_result);
	}
	return (0);
}

void	*pop_args(va_list args, char s)
{
	if (!s)
		return (0);
	else if (s == 'p')
		return (va_arg(args, void *));
	else if (s == 's')
		return (va_arg(args, char *));
	else if (s == 'c' || s == 'd' || s == 'u'
		|| s == 'i' || s == 'x' || s == 'X')
		return (malloc_arg(args, s));
	else
		return (0);
}
