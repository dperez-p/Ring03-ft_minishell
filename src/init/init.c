/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 12:19:42 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/12 12:30:26 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_data	*init_minishell(char **ev)
{
	t_data	*minishell;

	minishell = malloc(sizeof(t_data));
	if (!minishell)
		handle_error(MALLOC_ERROR);
	minishell->prompt = YELLOW "minishell$ " RESET;
	minishell->ev = ev;
	minishell->status = 0;
	minishell->ev_num = count_env_variables(ev);
	minishell->lev = init_env_list(ev);
	minishell->input = NULL;
	minishell->heredoc_num = 0;
	minishell->token = NULL;
	minishell->ast = NULL;
	return (minishell);
}
