/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:56:37 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 12:42:48 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* put character from file descriptor (id of a file asigned with open)*/
int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
