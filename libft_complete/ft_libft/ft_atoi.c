/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:04:29 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:35:28 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Asci to integer*/
int	ft_atoi(const char *nptr)
{
	int	a;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	a = 0;
	while (nptr[a] == ' ' || nptr[a] == '\t' || nptr[a] == '\n'
		|| nptr[a] == '\v' || nptr[a] == '\f' || nptr[a] == '\r')
	{
		a++;
	}
	if (nptr[a] == '-' || nptr[a] == '+')
	{
		if (nptr[a] == '-')
			sign = -1;
		a++;
	}
	while (nptr[a] >= '0' && nptr[a] <= '9')
	{
		result = result * 10 + (nptr[a] - '0');
		a++;
	}
	return (result * sign);
}
