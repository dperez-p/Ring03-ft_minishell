/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:29:32 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/23 19:43:12 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_redir(t_data *minishell, t_ast *ast, int id)
{
	int	file_fd;
	int	standard;
	int	status;

	ast->right->args = expansor(minishell, ast->right->right);
	if (check_file(ast, id)) //missing
		return (1);
	file_fd = get_filedescriptor(ast, id); //missing
	if (file_fd < 0)
		return (print_error(INVALID_FILE, 1, "open", ast->right->args));
	standard = get_standard(id); //missing
	if (dup2(file_fd, standard))
	{
		close(file_fd);
		handle_error(DUP_ERR);
	}
	close(file_fd);
	status = loop_tree(minishell, ast->left);
	if (dup2(minishell->fd_bk[0], STDIN_FILENO) == -1
		|| dup2(minishell->fd_bk[1], STDOUT_FILENO) == -1)
		handle_error(DUP_ERR);
	return (status);
}
