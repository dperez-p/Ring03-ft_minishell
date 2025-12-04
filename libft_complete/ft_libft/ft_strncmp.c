/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:39:50 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:06:45 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* Compare a number of characters of 2 strings */
int	ft_strncmp(const char	*s1, const char *s2, size_t n)
{
	size_t	a;

	if (n < 1)
	{
		return (0);
	}
	a = 0;
	while (s1[a] == s2[a] && s1[a] != '\0'
		&& s2[a] != '\0' && a < n - 1)
	{
		a++;
	}
	return ((unsigned char)s1[a] - (unsigned char)s2[a]);
}
