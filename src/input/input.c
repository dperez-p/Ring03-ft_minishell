/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:02:33 by dperez-p          #+#    #+#             */
/*   Updated: 2025/12/30 19:15:44 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_input(t_data *minishell)
{
	char	*input;
	int		status;

	input = readline(minishell->prompt);
	if (g_signal == SIGINT)
		update_exit_status(minishell, SIGINT + 130);
	if (!input)
	{
		printf("exit\n");
		finish(minishell);
	}
	if (*input)
		add_history(input);
	status = check_syntax(input);
	if (status != 0)
	{
		update_exit_status(minishell, status);
		free(input);
		return (NULL);
	}
	return (input);
}
