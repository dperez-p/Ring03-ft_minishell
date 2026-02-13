/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:05:59 by dperez-p          #+#    #+#             */
/*   Updated: 2025/07/01 10:02:03 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Count the leng of the hex*/
static int	ft_put_digits(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

/*Pointer to hex using recurisvity */
static void	ft_put_ptr(unsigned long long num)
{
	static char	digits[] = "0123456789abcdef";

	if (num >= 16)
		ft_put_ptr(num / 16);
	write(1, &digits[num % 16], 1);
}

/*Print the adress of a pointer or any variable,
output is in hexadecimal value.*/

int	ft_print_ptr(void *ptr)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	ft_put_ptr((unsigned long long)ptr);
	return (ft_put_digits((unsigned long long)ptr) + 2);
}
