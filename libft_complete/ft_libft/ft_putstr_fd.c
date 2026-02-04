/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:59:26 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 12:49:23 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* put string from file descriptor */
int	ft_putstr_fd(char *s, int fd)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		write(fd, &s[a], 1);
		a++;
	}
	return (a);
}
