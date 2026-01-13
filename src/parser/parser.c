/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:08 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/13 13:00:49 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to create a new AST node */
t_ast	*new_node(int id)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		handle_error(MALLOC);
	node->id = id;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* Frees the memory allocated for an AST node and its children */
void	free_ast(t_ast *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
	return ;
}

/* Main function to build the AST from the token list */
t_ast	*build_tree(t_data *minishell, t_token *token)
{
	t_token	*operator;

	if (is_subshell(token))
		return (parse_subshell(minishell, token));
	operator = find_main_operator(token);
	if (operator)
		return (parse_operator(minishell, token, operator));
	operator = search_pipeline(token);
	if (operator)
		return (parse_operator(minishell, token, operator));
}
