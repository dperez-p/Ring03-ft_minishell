/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:14:30 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:54:12 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/* Similar to memcpy with overflow security */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*temp;
	char		*destino;

	destino = (char *)dest;
	temp = (const char *)src;
	if (!dest && !src)
	{
		return (0);
	}
	if (destino >= temp)
	{
		while (n--)
		{
			destino[n] = temp[n];
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
