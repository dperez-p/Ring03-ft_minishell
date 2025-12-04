/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:56:37 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 08:54:46 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* put character from file descriptor (id of a file asigned with open)*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
