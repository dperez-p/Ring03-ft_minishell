/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:22:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 19:55:08 by dperez-p         ###   ########.fr       */
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

/* Helper function to find the matching closing parenthesis */
static t_token	*find_matching_end(t_token *token)
{
	int		rec;
	t_token	*curr;

	rec = 1;
	curr = token->next;
	while (curr)
	{
		if (curr->id == PAREN_OPEN)
			rec++;
		else if (curr->id == PAREN_CLOSE)
		{
			rec--;
			if (rec == 0)
				return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

/* Function to remove outer parentheses from a token list */
t_token	*remove_outer_parentheses(t_token *token)
{
	t_token	*end;
	t_token	*new;

	if (!token || token->id != PAREN_OPEN)
		return (token);
	end = find_matching_end(token);
	if (!end)
		return (token);
	new = token->next;
	if (token->next == end)
		new = NULL;
	else
	{
		token->next->prev = NULL;
		end->prev->next = NULL;
	}
	free_token_node(token);
	free_token_node(end);
	return (new);
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
		current = current->next;
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
