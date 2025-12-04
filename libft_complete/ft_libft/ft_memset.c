/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:52:57 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:54:20 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* memory set */
void	*ft_memset(void *s, int a, size_t n)
{
	char	*str;
	size_t	b;

	str = (char *)s;
	b = 0;
	while (n > b)
	{
		str[b] = a;
		b++;
	}
	return (str);
}
