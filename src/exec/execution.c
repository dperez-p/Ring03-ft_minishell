/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:48:30 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/16 10:58:27 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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


int	loop_tree(t_data *minishell, t_ast *ast)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (ast == NULL)
		return (0);
	if (ast->args == NULL)
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
		result = operators_command(minishell, ast); //missing function
	return (result);
}
