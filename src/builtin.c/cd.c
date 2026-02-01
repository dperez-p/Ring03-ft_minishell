/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlghar <najlghar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:09:49 by najlghar          #+#    #+#             */
/*   Updated: 2026/01/31 11:26:40 by najlghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	cd_error_args(char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("minishell: cd: missing operand", STDERR_FILENO);
		return (1);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	cd_chdir_error(char *path, char *old_pwd)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	free(old_pwd);
	return (1);
}

static void	update_pwd_vars(t_lev **lev, char *old_pwd)
{
	char	*new_pwd;

	update_env_var(lev, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_var(lev, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	cd(t_lev **lev, char **args)
{
	char	*old_pwd;

	if (cd_error_args(args))
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (chdir(args[1]) != 0)
		return (cd_chdir_error(args[1], old_pwd));
	update_pwd_vars(lev, old_pwd);
	free(old_pwd);
	return (0);
}
