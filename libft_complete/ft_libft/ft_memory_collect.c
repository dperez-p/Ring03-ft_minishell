/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory_collect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:38:07 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/06 18:14:43 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates memoryWrapper for calloc */
void	*allocate_mem(size_t nmemb, size_t size)
{
	return (ft_calloc(nmemb, size));
}

/* Frees memory Wrapper for free */
void	deallocate_mem(void *content)
{
	free(content);
}
