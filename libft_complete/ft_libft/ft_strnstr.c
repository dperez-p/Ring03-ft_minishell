/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:19:49 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:43:56 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/* return a pointer to the first occurrence of the substring needle in 
 * the string haystack.*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!*little)
	{
		return ((char *)big);
	}
	while (big[a])
	{
		b = 0;
		while (big[a] == little[b] && little[b] != '\0' && a < len)
		{
			if (little[b + 1] == '\0')
			{
				return ((char *)&big[a - b]);
			}
			b++;
			a++;
		}
		a = a - b + 1;
	}
	return (0);
}
