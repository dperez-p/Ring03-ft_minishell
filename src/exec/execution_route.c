/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:16:05 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:30:35 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Close fd to prevent extra files for children and
		execute extern command envp */
void	execute_child_command(char *command, char **args, t_data *minishell)
{
	struct stat	file_status;
	char		**envp;

	close_fd(minishell->fd_bk);
	if (stat(command, &file_status) == 0)
	{
		envp = convert_lev_to_array(minishell);
		execve(command, args, envp);
	}
	restore_fd(minishell->fd_bk);
	exit(print_error(EXECVE, 126, command, NULL));
}

/* Waits for child process and captures its exit status. returns the exit
	code if successful, or 128 + signal number if terminated by a signal */
int	execute_parent_command(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
	}
	return (WTERMSIG(status) + 128);
}

/* Finds the path, forks a child, and handles parent/child
 	coordination until the process exits.*/
int	execution_route(t_data *minishell, char **args)
{
	pid_t	pid;
	int		result;
	char	*command;

	result = 0;
	command = find_command(minishell, args[0], &result);
	if (!command)
		return (print_command_error(result, args[0]));
	pid = fork();
	setup_signals(pid);
	if (pid == 0)
		execute_child_command(command, args, minishell);
	else if (pid > 0)
		result = execute_parent_command(pid);
	else if (pid == -1)
		handle_error(FORK);
	deallocate_mem(command);
	return (result);
}
