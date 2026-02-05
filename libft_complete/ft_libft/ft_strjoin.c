/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:08:36 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:49:53 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/* put string S2 to the end of string S1, only set null at the end*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		count;
	char	*new;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		new = allocate_mem(l1 + l2 + 1, sizeof(char));
		if (!new)
			return (0);
		count = -1;
		while (s1[++count])
			new[count] = s1[count];
		count = -1;
		while (s2[++count])
		{
			new[l1] = s2[count];
			l1++;
		}
		new[l1] = '\0';
		return (new);
	}
	return (0);
}
