/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_submodule.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlghar <najlghar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 10:31:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/11 14:02:34 by najlghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Create a child process (fork) to execute a subtree, wait for it
 to finish, and return its exit status, cleaning up the child's memory */
int	execute_submodule(t_data *minishell, t_ast *ast)
{
	pid_t	submod_pid;
	int		status;

	submod_pid = fork();
	if (submod_pid == 0)
	{
		status = loop_tree(minishell, ast);
		close_fd(minishell->fd_bk);
		free_minishell(minishell);
		exit(status);
	}
	else
	{
		waitpid(submod_pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (128 + WTERMSIG(status));
	}
	return (0);
}
