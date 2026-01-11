/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:50:39 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/11 13:31:48 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Function to clean up minishell data structures */
void	finish(t_data *minishell)
{
	int	exit_status;

	if (g_signal == SIGINT)
		exit_status = 130;
	else
		exit_status = minishell->status;
	clean_minishell(minishell);
	free(minishell);
	exit(exit_status);
}

/* Function to run the main loop of the shell */
static void	run(t_data *minishell)
{
	t_ast	*ast;

	while (1)
	{
		iteration_init(minishell);
		minishell->input = get_input(minishell);
		if (minishell->input != NULL && !check_empty_input(minishell->input))
		{
			minishell->token = tokenize_input(minishell->input);
			if (check_syntax(minishell, *minishell->token) == 0)
			{
				ast = build_tree(minishell, minishell->token);
			}
			
		}
		
	}
}

/* Main function */
int	main(int ac, char **av, char **ev)
{
	t_data	*minishell;

	(void)av;
	if (ac != 1)
	{
		handle_error(USAGE);
	}
	if (!ev)
	{
		handle_error(EV);
	}
	minishell = init_minishell(ev);
	run(minishell);
	finish(minishell);
	return (0);
}
