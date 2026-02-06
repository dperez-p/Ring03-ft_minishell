/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:03:59 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/06 18:11:38 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Allocate memory for an array of nmemb elements of size bytes each
and returns a pointer to the allocated memory. The memory is set to zero */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	result = malloc(nmemb * size);
	if (!result)
	{
		return (0);
	}
	else
	{
		ft_bzero (result, (nmemb * size));
		return (result);
	}
}
