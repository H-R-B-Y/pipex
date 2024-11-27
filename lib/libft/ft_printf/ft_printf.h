/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:11:55 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/18 13:05:28 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>

typedef enum escflags_e
{
	non_f		= 0,
	hsh_f		= (1 << 0),
	qot_f		= (1 << 1),
	zro_f		= (1 << 2),
	min_f		= (1 << 3),
	dot_f		= (1 << 4),
	spc_f		= (1 << 5),
	add_f		= (1 << 6),
	len_f		= (1 << 7)
}				t_escflags;

typedef struct conv_s
{
	size_t			min_width;
	size_t			precision;
	unsigned int	flags;
	int				is_negative;
	char			type;
	void			*value;
	char			*control;
	char			*prefix;
	char			*output;
}					t_conv;

// bitflags.c

// Checks if a flag is set.
int		test_flag(unsigned int flags, t_escflags flag);

// Sets a flag.
void	set_flag(unsigned int *flags, t_escflags flag);

// Unsets a flag.
void	unset_flag(unsigned int *flags, t_escflags flag);

// Reads the escaped string in c, sets the flags
// accordingly. Except for dot_f which is set in parse precision.
t_conv	*set_conversion_flags(t_conv *c);

// Corrects the flags in c, certain flags override eachother,
// this function corrects that.
// Invalid combindations are:
// zro_f and dot_f = dot_f
// add_f and spc_f = add_f
// zro_f and min_f = min_f
t_conv	*correct_flags(t_conv *c);

// conv_factory.c

// Generates a conversion struct from the given string and value.
t_conv	*generate_conversion(char *str, void *value);

// Deletes a conversion struct and malloc'd values.
void	delete_conversion(t_conv *c);

// Returns the length of the printed string.
size_t	printed_length(t_conv *c);

// Prints the conversion.
void	print_conversion(t_conv *c);

// conversion_functions.c
char	*int_to_str(int *v);
char	*uint_to_str(unsigned int *v);
char	*uint_to_hex(unsigned int *v);
char	*ptr_to_hex(void *ptr);

// flag_functions.c

// Adds padding to either the prefix or the output flag dependant.
t_conv	*set_padding(t_conv *c);

// Sets the prefix for the conversion.
t_conv	*set_prefix(t_conv *c);

// ft_printf.c

// Handles the escape sequence in the string.
int		handle_escape(const char **str, va_list args, unsigned long long *len);

// Handles the majority of printing in the string. (calls handle escape on %)
int		ft_printf(const char *str, ...);

// general_functions.c

// Wraps the ft_toupper function for use in ft_striteri.
void	to_upper_wrapper(unsigned int x, char *c);

// Joins two strings and frees the input strings (if flags are set).
// OR dupes a string if only one is present.
char	*str_join_and_free(char *s1, char *s2, unsigned int flag);

// Zeroes out a memory block. (returns the pointer)
void	*zeroit(void *ptr, size_t n);

// Creates padding for the conversion, will create with either 0 or ' '.
char	*create_padding(t_conv *c);

// Reads from str until a non-numeric character is found.
// The substring is then converted to an integer and stored in value.
void	substr_atoi(char *str, size_t *value);

// generators.c

// Handles generating char and string outputs.
void	char_and_string(t_conv *c);

// Handles numeric outputs.
void	numerics(t_conv *c);

// Handles pointer and % outputs.
// Also prepends precision.
// Also converts the output to uppercase if the type is X.
t_conv	*generate_output(t_conv *c);

// precision.c

// Truncates the output to the precision for 
// string conversions.
t_conv	*truncate_precision(t_conv *c);

// Prepends the precision to the output.
t_conv	*prepend_precision(t_conv *c);

// escape_parsing.c

// Dupes the escape sequence in the string.
char	*pop_escaped_str(char **str);

// Parses the width from the escape sequence.
t_conv	*parse_width(t_conv *c, va_list args);

// Parses the precision from the escape sequence.
t_conv	*parse_precision(t_conv *c, va_list args);

void	*pop_args(va_list args, char s);

#endif