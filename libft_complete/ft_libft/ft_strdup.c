/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:00:10 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:59:14 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <stdlib.h>

/* set the size with malloc and duplicate the string */
char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;
	int		a;

	size = 0;
	while (s[size])
	{
		size++;
	}
	str = malloc(sizeof(char) * (size + 1));
	a = 0;
	if (!str)
	{
		return (0);
	}
	while (s[a])
	{
		str[a] = s[a];
		a++;
	}
	str[a] = '\0';
	return (str);
}
