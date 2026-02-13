/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:08:07 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/02 19:16:39 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to search for the last PIPE token at the top level */
t_token	*search_pipeline(t_token *token)
{
	t_token	*current;
	t_token	*last;
	int		parenthesis_count;

	current = token;
	last = NULL;
	parenthesis_count = 0;
	while (current)
	{
		if (current->id == PAREN_OPEN)
			parenthesis_count++;
		else if (current->id == PAREN_CLOSE)
			parenthesis_count--;
		else if (current->id == PIPE && parenthesis_count == 0)
			last = current;
		current = current->next;
	}
	return (last);
}

/* Function to find the main operator in a list of tokens */
t_token	*find_main_operator(t_token *token)
{
	t_token	*current;
	t_token	*main_operator;
	int		parenthesis_count;

	current = token;
	main_operator = NULL;
	parenthesis_count = 0;
	while (current)
	{
		if (current->id == PAREN_OPEN)
			parenthesis_count++;
		else if (current->id == PAREN_CLOSE)
			parenthesis_count--;
		else if ((current->id == AND || current->id == OR
				|| current->id == PIPE) && parenthesis_count == 0)
			main_operator = current;
		current = current->next;
	}
	return (main_operator);
}

/* Function to search for the first redirection token at the top level */
t_token	*search_redir(t_token *token)
{
	t_token	*current;
	int		parenthesis_count;

	current = token;
	parenthesis_count = 0;
	while (current)
	{
		if (current->id == PAREN_OPEN)
			parenthesis_count++;
		else if (current->id == PAREN_CLOSE)
			parenthesis_count--;
		else if ((current->id == REDIR_IN || current->id == REDIR_OUT
				|| current->id == HEREDOC || current->id == APPEND)
			&& parenthesis_count == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
