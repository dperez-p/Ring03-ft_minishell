/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:55:17 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 20:02:24 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Helper function to create a redirection AST node */
static t_ast	*get_redir_node(t_data *minishell, t_token *token,
	t_token *operator)
{
	t_ast	*node;
	t_token	*left_tokens;
	t_token	*right_tokens;

	node = new_node(operator->id);
	if (!node)
		handle_error(MALLOC);
	left_tokens = token;
	right_tokens = operator->next;
	if (operator->prev)
	{
		operator->prev->next = NULL;
		operator->next = NULL;
	}
	free_token_node(operator);
	node->left = build_tree(minishell, left_tokens);
	node->right = build_tree(minishell, right_tokens);
	return (node);
}

/* Function to parse a redirection operator and build
			the corresponding AST node */
t_ast	*parse_redir(t_data *minishell, t_token *token, t_token *operator)
{
	if (!token || !operator)
		return (NULL);
	if (token == operator)
	{
		token = token->next->next;
		if (token)
			token->prev = NULL;
		operator->next->next = NULL;
	}
	else
	{
		operator->prev->next = operator->next->next;
		if (operator->next->next)
			operator->next->next->prev = operator->prev;
		if (operator->next)
			operator->next->next = NULL;
		operator->prev = NULL;
	}
	if (operator->id == HEREDOC)
		parse_heredoc(minishell, operator);
	return (get_redir_node(minishell, token, operator));
}

/* Function to parse an operator and build the corresponding AST node */
t_ast	*parse_operator(t_data *minishell, t_token *token, t_token *operator)
{
	t_ast	*node;
	t_token	*right_tokens;

	if (!token || !operator)
		return (NULL);
	node = new_node(operator->id);
	if (!node)
		handle_error(MALLOC);
	right_tokens = split_token_list(token, operator);
	free_token_node(operator);
	node->left = build_tree(minishell, token);
	node->right = build_tree(minishell, right_tokens);
	return (node);
}

/* Parses a simple command (ARG tokens) into an AST node */
t_ast	*parse_token(t_token *token)
{
	t_ast	*node;
	int		count;
	t_token	*tmp;

	if (!token || token->id != ARG)
		return (NULL);
	node = new_node(token->id);
	count = arg_count(token);
	node->args = malloc(sizeof(char *) * (count + 1));
	if (!node->args)
		handle_error(MALLOC);
	count = 0;
	while (token && token->id == ARG)
	{
		node->args[count] = ft_strdup(token->value);
		if (!node->args[count])
			handle_error(MALLOC);
		count++;
		tmp = token;
		token = token->next;
		free_token_node(tmp);
	}
	node->args[count] = NULL;
	return (node);
}

/* Parses a subshell expression into an AST node */
t_ast	*parse_subshell(t_data *minishell, t_token *token)
{
	t_ast	*node;

	token = remove_outer_parentheses(token);
	node = new_node(SUBSHELL);
	if (!node)
		handle_error(MALLOC);
	node->left = build_tree(minishell, token);
	return (node);
}
