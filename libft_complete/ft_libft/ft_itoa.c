/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:44:13 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:39:53 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* Integer to ASCII */
static int	ft_numlen(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len = 1;
	}
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	len;
	char		*result;
	long int	num;

	num = n;
	len = ft_numlen(n);
	result = (char *)malloc((len + 1) * (sizeof(char)));
	if (!result)
		return (0);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		result[0] = '-';
		num = num * -1;
	}
	while (num > 0)
	{
		result[len--] = (num % 10) + '0';
		num = num / 10;
	}
	return (result);
}
