/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:22:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/06 18:48:04 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to remove outer parentheses from a token list */
t_token	*remove_outer_parentheses(t_token *token)
{
	t_token	*current;
	t_token	*new_start;
	t_token	*new_end;

	if (!token || token->id != PAREN_OPEN)
		return (token);
	current = token;
	while (current && current->id != PAREN_CLOSE)
		current = current->next;
	if (!current)
		return (token);
	new_start = token->next;
	new_end = current->prev;
	if (new_start)
		new_start->prev = NULL;
	if (new_end)
		new_end->next = NULL;
	return (new_start);
}

/* Function to check if the tokens form a valid shellcommand structure */
int	is_subshell(t_token *token)
{
	t_token	*last;
	t_token	*current;
	int		parenthesis_count;

	if (!token || token->id != PAREN_OPEN)
		return (0);
	last = token;
	while (last->next)
		last = last->next;
	if (last->id != PAREN_CLOSE)
		return (0);
	parenthesis_count = 0;
	current = token;
	while (current)
	{
		if (current->id == PAREN_OPEN)
			parenthesis_count++;
		else if (current->id == PAREN_CLOSE)
			parenthesis_count--;
		if (parenthesis_count == 0 && current != last)
			return (0);
	}
	return (1);
}
