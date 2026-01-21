/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 09:26:57 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/21 10:05:47 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Redirects input/output to the pipe, executes the command,
	and closes the child process. */
static void	pipe_children(t_data *minishell, t_ast *ast, int fd[2], int index)
{
	int	status;

	if (dup2(fd[index], index == -1))
		handle_error(DUP_ERR);
	close_fd(fd);
	status = loop_tree(minishell, ast);
	close_fd(minishell->fd_bk);
	clear_mem();
	exit(status);
}

static void	wait_status(pid_t pid, int	*status)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (*status == 1)
		return ;
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
}

/* Create a pipe and two children: one writes (left),
 the other reads (right) and returns the status. */
int	execution_pipe(t_data *minishell, t_ast *ast)
{
	int		fd[2];
	int		status[2];
	pid_t	children_pid[2];

	if (pipe(fd) == -1)
		handle_error(PIPE_ERR);
	children_pid[0] = fork();
	if (children_pid[0] == -1)
		handle_error(FORK);
	setup_signal(children_pid[0]);
	if (children_pid[0] == 0)
		pipe_children(minishell, ast->left, fd, STDOUT_FILENO);
	children_pid[1] = fork();
	setup_signal(children_pid[1]);
	if (children_pid[1] == 0)
		pipe_children(minishell, ast->right, fd, STDIN_FILENO);
	close_fd(fd);
	wait_status(children_pid[0], &status[0]);//missing
	wait_status(children_pid[1], &status[1]);//missing
	if (status[0] == SIGINT + 128)
		return (status[0]);
	return (status[1]);
}
