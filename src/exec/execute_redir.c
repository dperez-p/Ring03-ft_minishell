/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:29:32 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/13 11:09:33 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Check whether the file has read or write permissions
 depending on the type of redirection (input or output) */
static int	check_file_permission(t_ast *ast, int id)
{
	char	*filename;

	filename = ast->right->args[0];
	if (id == REDIR_OUT || id == APPEND)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) != 0)
			return (0);
	}
	else
	{
		if (access(filename, F_OK) == 0 && access(filename, R_OK) != 0)
			return (0);
	}
	return (1);
}

/* Validate a file: ensure the name is not empty, that
 it is a unique path, and that access permissions exist */
static int	check_file(t_ast *ast, int id)
{
	if (!ast->right || (ast->right && !ast->right->args[0]))
		return (print_error(INVALID_FILE, 1, "open", NULL));
	if (ast->right && ast->right->args && ast->right->args[1])
		return (print_error(AMBIGUOUS_REDIR, 1, NULL, NULL));
	if (!check_file_permission(ast, id))
		return (print_error(INVALID_PERM, 1, NULL, NULL));
	return (0);
}

/* Open the appropriate file according to the type of redirection
 (write, append, or read) and return its file descriptor (fd) */
static int	get_filedescriptor(t_ast *ast, int id)
{
	int		file_fd;
	char	*filename;

	filename = ast->right->args[0];
	if (id == REDIR_OUT)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (id == APPEND)
		file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	else
		file_fd = open(filename, O_RDONLY);
	return (file_fd);
}

/* Return the standard file descriptor (input or output) that
 will be replaced based on the detected redirection type */
static int	get_standard(int id)
{
	if (id == REDIR_OUT || id == APPEND)
		return (STDOUT_FILENO);
	return (STDIN_FILENO);
}

/* Execute the redirection: expand variables, validate the file, redirect file
 descriptors (dup2), process the command, and restore the standard streams */
int	execute_redir(t_data *minishell, t_ast *ast, int id)
{
	int	file_fd;
	int	standard;
	int	status;

	ast->right->args = expansor(minishell, ast->right->args);
	if (check_file(ast, id))
		return (1);
	file_fd = get_filedescriptor(ast, id);
	if (file_fd < 0)
		return (print_error(INVALID_FILE, 1, "open", ast->right->args[0]));
	standard = get_standard(id);
	if (dup2(file_fd, standard) == -1)
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
