/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 08:49:17 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:13:46 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

/* return part of the string */
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s)
	{
		return (0);
	}
	if (ft_strlen(s) < start)
	{
		return (ft_strdup(""));
	}
	if (ft_strlen (s + start) < len)
	{
		len = ft_strlen(s + start);
	}
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		return (0);
	}
	ft_strlcpy(res, (char *)s + start, len + 1);
	return (res);
}
