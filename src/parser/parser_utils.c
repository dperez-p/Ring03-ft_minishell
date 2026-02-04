/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:22:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 16:25:42 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to count the number of ARG tokens in a token list */
int	arg_count(t_token *token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while (current && current->id == ARG)
	{
		count++;
		current = current->next;
	}
	return (count);
}

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

/* Function to split the token list at the operator */
t_token	*split_token_list(t_token *token, t_token *operator)
{
	t_token	*right;

	right = NULL;
	if (!token || !operator)
		return (NULL);
	if (operator->next)
	{
		right = operator->next;
		right->prev = NULL;
	}
	if (operator->prev)
		operator->prev->next = NULL;
	operator->prev = NULL;
	operator->next = NULL;
	return (right);
}
