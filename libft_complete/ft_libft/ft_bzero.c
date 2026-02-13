/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:34:33 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:37:07 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* Set number of chars to 0*/
void	*ft_bzero(void *s, size_t n)
{
	char	*str;
	int		a;
	size_t	b;

	str = (char *)s;
	b = 0;
	a = '\0';
	while (n > b)
	{
		str[b] = a;
		b++;
	}
	return (s);
}
