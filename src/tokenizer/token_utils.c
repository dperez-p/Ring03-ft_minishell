/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:33:55 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 19:55:08 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Creates a new token with the given value and ID */
t_token	*create_token(char *value, int id)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		handle_error(MALLOC);
	new_token->id = id;
	new_token->value = value;
	if (!new_token->value)
		handle_error(MALLOC);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

/* Adds a token to the end of the token list */
void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (*tokens == NULL)
	{
		*tokens = new_token;
	}
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}

/* Frees the entire token list */
void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

/* Frees a single token node */
void	free_token_node(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
