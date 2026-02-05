/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:03:59 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:50:57 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Allocates memory for an array of nmemb elements of size bytes each and
   initializes all bytes to zero. Returns a pointer to the allocated memory,
   or NULL if the allocation fails or if nmemb or size is zero. */
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*dest;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	total = nmemb * size;
	dest = malloc(total);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, total);
	return (dest);
}
