/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:10:20 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:04:44 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/* concatenate a size of characters from src to dst saving
the last char to set NULL*/
int	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	sizedst;
	size_t	sizesrc;
	size_t	a;

	sizedst = ft_strlen(dst);
	sizesrc = ft_strlen(src);
	if (!size)
	{
		return (sizesrc);
	}
	if (size <= sizedst)
	{
		return (size + sizesrc);
	}
	a = 0;
	while (a < (size - sizedst - 1) && src[a] != '\0')
	{
		dst[sizedst + a] = src[a];
		a++;
	}
	dst[sizedst + a] = '\0';
	return (sizedst + sizesrc);
}
