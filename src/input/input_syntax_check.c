/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:37:54 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/28 14:14:04 by dperez-p         ###   ########.fr       */
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
	if (token->next->id != ARG && token->next->id != PAREN_OPEN
		&& !(token->next->id >= REDIR_IN && token->next->id <= APPEND))
		return (print_error(SYNTAX, 2, NULL, token->next->value));
	return (0);
}

/* Validates that every redirection is mandatory followed by an argument 
 returns 0 if valid, or a syntax error if the destination is missing */
static int	redir_rule(t_token *token)
{
	if (!token->next)
		return (print_error(SYNTAX, 2, NULL, token->value));
	if (token->next->id != ARG)
		return (print_error(SYNTAX, 2, NULL, token->next->value));
	return (0);
}

/* Validates the position of parentheses relative to their neighboring tokens
 returns 0 if the syntax is correct, or an error if the sequence is invalid */
static int	paren_rule(t_token *token)
{
	if (token->id == PAREN_OPEN)
	{
		if (token->prev && token->prev->id >= PAREN_CLOSE)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
		if (!token->next || (token->next->id != ARG
				&& token->next->id != PAREN_OPEN))
			return (print_error(SYNTAX, 2, NULL, token->next->value));
	}
	if (token->id == PAREN_CLOSE)
	{
		if (!token->prev)
			return (print_error(SYNTAX, 2, NULL, token->value));
		if (token->prev->id != ARG && token->prev->id != PAREN_CLOSE)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
		if (token->next && token->next->id == ARG)
			return (print_error(SYNTAX, 2, NULL, token->prev->value));
	}
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
