/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:48:30 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 18:21:04 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Execute AND "function" */
static int	execute_and(t_data *minishell, t_ast *ast)
{
	int	result;

	result = 0;
	if (ast->left)
		result = loop_tree(minishell, ast->left);
	if (result == 0 && ast->right)
		result = loop_tree(minishell, ast->right);
	return (result);
}

/* Execute OR "function" */
static int	execute_or(t_data *minishell, t_ast *ast)
{
	int	result;

	result = 0;
	if (ast->left)
		result = loop_tree(minishell, ast->left);
	if (result != 0 && ast->right)
		result = loop_tree(minishell, ast->right);
	return (result);
}

/* Execute the command represented by the AST */
int	execute_command(t_data *minishell)
{
	int	result;

	result = loop_tree(minishell, *minishell->ast);
	if (dup2(minishell->fd_bk[0], STDIN_FILENO) == -1
		|| dup2(minishell->fd_bk[1], STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	close_fd(minishell->fd_bk);
	restore_fd(minishell->fd_bk);
	return (result);
}

/* Act as a command dispatcher: identify the operator type
 (AND, OR, PIPE, REDIR, or SUBSHELL) and call its execution function */
int	operators_command(t_data *minishell, t_ast *ast)
{
	int	result;

	result = 0;
	if (ast->id == AND)
		result = execute_and(minishell, ast);
	else if (ast->id == OR)
		result = execute_or(minishell, ast);
	else if (ast->id == PIPE)
		result = execute_pipe(minishell, ast);
	else if (ast->id >= REDIR_IN && ast->id <= APPEND)
		result = execute_redir(minishell, ast, ast->id);
	else if (ast->id == SUBSHELL)
		result = execute_submodule(minishell, ast->left);
	return (result);
}

/* Traverses the tree and executes the corresponding command */
int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (ast == NULL)
		return (0);
	if (ast->args != NULL)
	{
		ast->args = expansor(minishell, ast->args);
		while (ast->args[i] && ast->args[i][0] == '\0')
			i++;
		if (!ast->args[i])
			return (0);
		result = command_menu(minishell, &ast->args[i]);
		if (result == -1)
			result = execution_route(minishell, &ast->args[i]);
	}
	else
		result = operators_command(minishell, ast);
	return (result);
}
