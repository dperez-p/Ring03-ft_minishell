/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:48:11 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/16 10:59:52 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Command menu, Identifies and executes shell built-ins compares args[0]
with the built-in list. Returns the function's result if matched or -1 */
int	command_menu(t_data *minishell, char **args)
{
	if (!ft_strncmp(args[0], "echo", 4) && ft_strlen(args[0]) == 4)
		return (echo(args));
	if (!ft_strncmp(args[0], "cd", 2) && ft_strlen(args[0]) == 2)
		return (cd(minishell->lev, args));
	if (!ft_strncmp(args[0], "pwd", 3) && ft_strlen(args[0]) == 3)
		return (pwd(minishell));
	if (!ft_strncmp(args[0], "export", 6) && ft_strlen(args[0]) == 6)
		return (export(minishell, args));
	if (!ft_strncmp(args[0], "unset", 5) && ft_strlen(args[0]) == 5)
		return (unset(minishell, args));
	if (!ft_strncmp(args[0], "env", 3) && ft_strlen(args[0]) == 3)
		return (env(minishell->lev, args));
	if (!ft_strncmp(args[0], "exit", 4) && ft_strlen(args[0]) == 4)
		return (exec_exit(minishell, args));
	return (-1);
}
