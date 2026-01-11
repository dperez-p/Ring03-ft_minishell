/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:37:54 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/11 19:32:47 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Syntax rule for redirection operators */
static int	operators_rule(t_token *token)
{
	if (token->prev == NULL || token->next == NULL)
		return (print_error(SYNTAX, 2, NULL, token->value));
	if (token->prev->id != ARG && token->prev->id != PAREN_CLOSE)
		return (print_error(SYNTAX, 2, NULL, token->prev->value));
	if (token->next->id >= REDIR_IN && token->next->id <= APPEND)
		return (print_error(SYNTAX, 2, NULL, token->next->value));
	return (0);
}

/* Main syntax checking function */
int	check_syntax(t_data *minishell, t_token *token)
{
	int	status;

	status = 0;
	while (token)
	{
		if (token->id == AND || token->id == OR || token->id == PIPE)
			status = operators_rule(token);
		else if (token->id >= REDIR_IN && token->id <= APPEND)
			status = redir_rule(token);
		else if (token->id == PAREN_OPEN || token->id == PAREN_CLOSE)
			status = paren_rule(token);
		if (status)
		{
			update_exit_status(minishell, status);
			return (status);
		}
		token = token->next;
	}
	return (status);
}
