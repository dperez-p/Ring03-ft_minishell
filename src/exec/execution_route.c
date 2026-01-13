/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:16:05 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/13 19:01:33 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_child_command(char *command, char **args, t_data *minishell)
{
	struct stat	file_status;
	char		**envp;

	close_fd(minishell->fd_bk);
	if (stat(command, &file_status) == 0)
	{
		envp = convert_lev_to_array(minishell);
	}
	
}

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
	setup_signal(pid);
	if (pid == 0)
		exec_child_command(command, args, minishell->envp);
	
}
