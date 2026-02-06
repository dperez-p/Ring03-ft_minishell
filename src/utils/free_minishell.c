/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:30:00 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/06 18:31:32 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Frees all memory allocated in the minishell structure */
void	free_minishell(t_data *minishell)
{
	if (!minishell)
		return ;
	if (minishell->lev)
		free_env_list(minishell->lev);
	if (minishell->token)
	{
		free_tokens(minishell->token);
		free(minishell->token);
	}
	if (minishell->ast && *minishell->ast)
		free_ast(*minishell->ast);
	if (minishell->ast)
		free(minishell->ast);
	if (minishell->input)
		free(minishell->input);
	free(minishell);
}
