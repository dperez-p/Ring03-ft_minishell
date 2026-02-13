/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 09:49:19 by dperez-p          #+#    #+#             */
/*   Updated: 2025/05/17 09:00:55 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* iterate a string with f fuction */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	a;

	a = 0;
	while (s[a])
	{
		f(a, s + a);
		a++;
	}
}
