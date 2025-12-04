/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:12:01 by dperez-p          #+#    #+#             */
/*   Updated: 2025/10/21 17:34:01 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*Set malloc to null*/
void	*ft_calloc(size_t num, size_t size)
{
	size_t	total;
	size_t	i;
	char	*buff;

	total = num * size;
	i = 0;
	buff = malloc(total);
	if (!buff)
		return (NULL);
	while (total-- > 0)
		buff[i++] = '\0';
	return ((void *)buff);
}

/* check the string untill find C */
bool	ft_get_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	return (false);
}

/* Count the leng of the string */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
