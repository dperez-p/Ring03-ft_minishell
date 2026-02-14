/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:43:31 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/14 17:32:50 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Signal handler for SIGINT during heredoc input */
void	handle_heredoc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_signal = SIGINT;
	close(STDIN_FILENO);
}

/* Signal handler for SIGPIPE in child processes */
void	handle_sigpipe(int signum)
{
	(void)signum;
}

/* Handle the SIGINT signal (Ctrl+C): clear the current line
 and refresh the prompt to receive a new command */
void	handle_ctrl_c(int sig)
{
	(void)sig;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = SIGINT;
}

/* Only move the cursor to a new line; used to prevent
the prompt from overlapping when a child command is interrupted */
void	handle_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd("", STDOUT_FILENO);
}
