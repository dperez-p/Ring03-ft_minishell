/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:07:45 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/01 13:27:51 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int	unset_one_var(t_data *minishell, char *arg)
{
	t_lev	*node;

	if (!is_valid_identifier(arg))
	{
		print_unset_error(arg);
		return (1);
	}
	node = findlev(*minishell->lev, arg);
	if (node)
	{
		remove_env_node(minishell->lev, node); //Missing function
		minishell->ev_num--;
	}
	return (0);
}

int	unset(t_data *minishell, char **args)
{
	int	i;
	int	error;

	if (!args[1])
		return (0);
	i = 1;
	error = 0;
	while (args[i])
	{
		if (unset_one_var(minishell, args[i]))
			error = 1;
		i++;
	}
	return (error);
}
