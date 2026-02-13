/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:19:42 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/06 18:49:16 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Initializes the main structure, sets up the prompt and environment, 
   and backs up the standard file descriptors (STDIN/STDOUT) */
t_data	*init_minishell(char **ev)
{
	t_data	*minishell;

	minishell = allocate_mem(1, sizeof(t_data));
	minishell->prompt = YELLOW "minishell$ " RESET;
	minishell->ev = ev;
	minishell->lev = init_env_list(minishell);
	minishell->fd_bk[0] = dup(STDIN_FILENO);
	minishell->fd_bk[1] = dup(STDOUT_FILENO);
	if (minishell->fd_bk[0] == -1 || minishell->fd_bk[1] == -1)
		handle_error(DUP_ERR);
	minishell->ast = malloc(sizeof(t_ast *));
	if (!minishell->ast)
		handle_error(MALLOC);
	*minishell->ast = NULL;
	minishell->heredoc_num = 0;
	minishell->status = 0;
	return (minishell);
}
