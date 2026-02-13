/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:59:26 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/13 10:49:28 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* put string from file descriptor */
int	ft_putstr_fd(char *s, int fd)
{
	int	a;

	if (!s)
		return (0);
	a = 0;
	while (s[a] != '\0')
	{
		write(fd, &s[a], 1);
		a++;
	}
	return (a);
}
