/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:15:11 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:05:18 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* copy a size of characters from src to dst saving
the last char to set NULL*/
int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	c;
	size_t	len;

	len = 0;
	c = 0;
	while (src[len] != '\0')
	{
		len++;
	}
	if (size < 1)
	{
		return (len);
	}
	while (src && src[c] != '\0' && c < size - 1)
	{
		dst[c] = src[c];
		c++;
	}
	dst[c] = '\0';
	return (len);
}
