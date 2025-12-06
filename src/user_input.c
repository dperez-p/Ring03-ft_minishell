/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 21:54:08 by dperez-p          #+#    #+#             */
/*   Updated: 2025/12/05 22:01:27 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	user_input(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL) // function not alowed make own
	{
		if (feof(stdin)) // function not allowed make own
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("fgets"); //change for printf
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}

// void	execute_command(const char *command)
// {
// 	pid_t
// }