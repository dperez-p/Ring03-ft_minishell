/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:39:47 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:57:15 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* Split a string when found C in array of 
mallocs with security for memory leaks */
static	size_t	ft_c_words(char	const *s, char c)
{
	size_t	count;

	if (!*s)
	{
		return (0);
	}
	count = 0;
	while (*s)
	{
		while (*s == c)
		{
			s++;
		}
		if (*s)
			count++;
		while (*s != c && *s)
		{
			s++;
		}
	}
	return (count);
}

static	size_t	ft_nchar(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
	{
		count++;
	}
	return (count);
}

static	char	**ft_free_array(const	char **result, size_t a)
{
	while (a--)
	{
		free((char *)result[a]);
	}
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	n_words;
	size_t	a;
	size_t	str_l;

	a = 0;
	n_words = ft_c_words(s, c);
	result = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!result || !s)
		return (NULL);
	while (a < n_words)
	{
		while (*s == c)
			s++;
		str_l = ft_nchar((const char *)s, c);
		result[a] = (char *)malloc(sizeof(char) * (str_l + 1));
		if (!result[a])
			return (ft_free_array((const char **)result, a));
		ft_strlcpy(result[a], s, str_l + 1);
		s += str_l;
		a++;
	}
	result[a] = 0;
	return (result);
}
