/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:29:08 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 17:38:16 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to create a new AST node */
t_ast	*new_node(int id)
{
	t_ast	*node;

	node = allocate_mem(1, sizeof(t_ast));
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
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	ft_free_matrix(node->args);
	deallocate_mem(node);
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
	operator = search_redir(token);
	if (operator)
		return (parse_redir(minishell, token, operator));
	return (parse_token(token));
}
