/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:02:33 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/28 13:53:34 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Reads the user input, manages signals and history, and verifies 
   that the syntax is valid before returning the read line. */
char	*get_input(t_data *minishell)
{
	char	*input;
	int		status;

	input = readline(minishell->prompt);
	if (g_signal == SIGINT)
		update_exit_status(minishell, SIGINT + 130);
	if (!input)
	{
		ft_putstr_fd("exit\n", 1);
		finish(minishell);
	}
	if (*input)
		add_history(input);
	status = check_input_syntax(input);
	if (status != 0)
	{
		update_exit_status(minishell, status);
		free(input);
		return (NULL);
	}
	return (input);
}
