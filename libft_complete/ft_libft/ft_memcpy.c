/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:38:43 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:53:47 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* Copy 2 memory space dest from src */
void	*ft_memcpy(void *dest, const void *src, size_t n)

{
	char		*destino;
	const char	*source;
	size_t		a;

	destino = (char *)dest;
	source = (const char *)src;
	a = 0;
	if (!dest && !src)
	{
		return (0);
	}
	while (n > a)
	{
		destino[a] = source[a];
		a++;
	}
	return (dest);
}
