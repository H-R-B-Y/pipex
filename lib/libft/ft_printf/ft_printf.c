/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:12:19 by hbreeze           #+#    #+#             */
/*   Updated: 2025/02/13 16:38:23 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	handle_escape(const char **str, va_list args, unsigned long long *len)
{
	char	*esc;
	void	*val;
	t_conv	*conversion;
	char	*tmp;

	tmp = (char *)*str;
	esc = pop_escaped_str((char **)str);
	if (!esc)
		return (*str = tmp, -1);
	val = pop_args(args, (char)*(*str - 1));
	conversion = generate_conversion(esc, val);
	if (!conversion)
		return (-1);
	set_conversion_flags(conversion);
	parse_precision(parse_width(conversion, args), args);
	generate_output(correct_flags(conversion));
	if (conversion->type != '%')
		set_padding(set_prefix(conversion));
	print_conversion(conversion);
	*len += printed_length(conversion);
	delete_conversion(conversion);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list				args;
	unsigned long long	len;

	len = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && !*(str + 1)
			&& (ft_putchar_fd('%', 1), ++len) && ++str)
			continue ;
		else if (*str == '%' && !handle_escape(&str, args, &len))
			continue ;
		else if (++len)
			ft_putchar_fd(*str, 1);
		str++;
	}
	return (va_end(args), len);
}
