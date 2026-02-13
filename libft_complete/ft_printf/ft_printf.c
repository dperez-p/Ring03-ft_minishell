/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:40:03 by dperez-p          #+#    #+#             */
/*   Updated: 2025/07/01 10:00:37 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Passing the format*/
static int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar('%'));
	return (1);
}

/*Main fuction*/
int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_l;

	i = 0;
	print_l = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			print_l += ft_format(args, str[i + 1]);
			i++;
		}
		else
		{
			print_l += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (print_l);
}
