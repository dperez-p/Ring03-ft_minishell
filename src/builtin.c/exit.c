/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlghar <najlghar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:04:11 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/11 13:58:04 by najlghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_numeric_error(t_data *minishell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	minishell->status = 2;
	finish(minishell);
}

static int	handle_too_many_args(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (1);
}

int	exec_exit(t_data *minishell, char **args)
{
	long long	exit_code;

	if (!args[1])
	{
		finish(minishell);
		exit(minishell->status);
	}
	if (!is_numeric(args[1]))
		handle_numeric_error(minishell, args[1]);
	if (args[2])
		return (handle_too_many_args());
	exit_code = ft_atoll(args[1]);
	minishell->status = exit_code;
	finish(minishell);
	return (0);
}
