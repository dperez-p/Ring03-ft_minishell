/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:18:07 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/23 11:16:57 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*conver to hex*/
int	ft_print_hex(unsigned int nbr, char *base)
{
	int	nbr_base[16];
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (nbr == 0)
		result = ft_putchar('0');
	while (nbr)
	{
		nbr_base[i] = nbr % 16;
		nbr = nbr / 16;
		i++;
	}
	while (--i >= 0)
		result += ft_putchar(base[nbr_base[i]]);
	return (result);
}
