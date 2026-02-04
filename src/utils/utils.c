/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:16:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 12:57:39 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Concatenate three strings into a new string */
char	*concatenate(const char *s1, const char *s2, const char *s3)
{
	char	*result1;
	char	*result2;

	result1 = ft_strjoin(s1, s2);
	if (!result1)
		return (NULL);
	result2 = ft_strjoin(result1, s3);
	free(result1);
	if (!result2)
		return (NULL);
	return (result2);
}

/* Close file descriptors if they are open */
void	close_fd(int *fd)
{
	if (fd[0] != -1)
	{
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
	}
}

/* Saves or restores the standard input and output file descriptors.*/
void	restore_fd(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1)
		handle_error(DUP_ERR);
}

/* Skip leading zeros in a numeric string */
int	skip_zeros(const char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i] == '0')
		i++;
	return (i);
}
