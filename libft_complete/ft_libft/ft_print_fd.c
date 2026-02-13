/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 12:41:23 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/13 11:00:58 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function to print a number in a specified base to a given file descriptor */
int	ft_putbase_fd(long long n, char *base, int div, int fd)
{
	int		count;
	char	c;

	count = 0;
	if (n < 0 && div == 10)
	{
		write (fd, "-", 1);
		count ++;
		n = -n;
	}
	c = base[n % div];
	if (n >= div)
		count += ft_putbase_fd(n / div, base, div, fd);
	count += ft_putchar_fd(c, fd);
	return (count);
}

/* Function to print a pointer address to a given file descriptor */
int	ft_putpointer_fd(unsigned long p, int fd)
{
	int		i;
	int		count;
	char	*base;
	char	str[17];

	i = 0;
	count = 0;
	base = "0123456789abcdef";
	if (!p || p == 0)
		return (ft_putstr_fd("(nil)", fd));
	count = ft_putstr_fd("0x", fd);
	while (p > 0)
	{
		str[i] = base[p % 16];
		p /= 16;
		i++;
	}
	count += i;
	i--;
	while (i >= 0)
		write(fd, &str[i--], 1);
	return (count);
}

/* Function to print a single character to a given file descriptor */
static int	ft_putstr_safe(char *s, int fd)
{
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(s, fd));
}

/* Helper function to verify format specifiers and call appropriate printing
functions */
int	ft_verify(char spec, va_list args, int fd)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count = ft_putchar_fd(va_arg(args, int), fd);
	else if (spec == 's')
		count = ft_putstr_safe(va_arg(args, char *), fd);
	else if (spec == 'd' || spec == 'i')
		count = ft_putbase_fd(va_arg(args, int), "0123456789", 10, fd);
	else if (spec == 'u')
		count = ft_putbase_fd(va_arg(args, unsigned int), "0123456789", 10, fd);
	else if (spec == 'x')
		count = ft_putbase_fd(va_arg(args, unsigned int),
				"0123456789abcdef", 16, fd);
	else if (spec == 'X')
		count = ft_putbase_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", 16, fd);
	else if (spec == 'p')
		count = ft_putpointer_fd(va_arg(args, unsigned long), fd);
	else if (spec == '%')
		count = ft_putchar_fd('%', fd);
	return (count);
}

/* Main function to print formatted output to a given file descriptor */
int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_verify(str[i], args, fd);
		}
		else
			count += ft_putchar_fd(str[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
