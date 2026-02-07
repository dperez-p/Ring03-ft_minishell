/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:50:39 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 19:06:06 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal;

/* Function to clean up minishell data structures */
void	finish(t_data *minishell)
{
	int	exit_status;

	if (g_signal == SIGINT)
		exit_status = 130;
	else
		exit_status = minishell->status;
	close_fd(minishell->fd_bk);
	free_minishell(minishell);
	exit(exit_status);
}

/* Updates the exit status of minishell */
void	update_exit_status(t_data *minishell, int status)
{
	minishell->status = status;
	g_signal = 0;
}

/* Prepares the environment for a new iteration: enables signals and clears
previous data  frees the previous input and removes temporary heredoc files */
static void	iteration_init(t_data *minishell)
{
	interactive_signals();
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->token)
	{
		free_tokens(minishell->token);
		free(minishell->token);
		minishell->token = NULL;
	}
	remove_heredoc_files(minishell);
}

/* Function to run the main loop of the shell */
static void	run(t_data *minishell)
{
	t_ast	*root;

	while (1)
	{
		iteration_init(minishell);
		minishell->input = get_input(minishell);
		if (minishell->input != NULL && !check_empty_input(minishell->input))
		{
			minishell->token = tokenize_input(minishell->input);
			if (check_syntax(minishell, *minishell->token) == 0)
			{
				root = build_tree(minishell, *minishell->token);
				if (!root)
					handle_error(MALLOC);
				*minishell->token = NULL;
				*minishell->ast = root;
				if (g_signal == SIGINT)
					update_exit_status(minishell, SIGINT + 128);
				else
					update_exit_status(minishell, execute_command(minishell));
				free_ast(root);
				*minishell->ast = NULL;
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
