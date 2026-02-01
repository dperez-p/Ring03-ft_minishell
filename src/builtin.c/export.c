/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:10:51 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/01 13:03:50 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

static int	handle_export_one(t_lev **lev, char *arg)
{
	char	*key;
	char	*value;
	int		append;

	parse_assignment(arg, &key, &value, &append);
	if (!is_valid_identifier(key))
	{
		free(key);
		free(value);
		return (export_error(arg));
	}
	export_variable(lev, key, value, append);
	free(key);
	free(value);
	return (0);
}

int	export(t_data *minishell, char **args)
{
	int	i;
	int	error;

	if (!args[1])
	{
		print_export(minishell->lev);
		return (0);
	}
	i = 1;
	error = 0;
	while (args[i])
	{
		if (handle_export_one(minishell->lev, args[i]))
			error = 1;
		i++;
	}
	return (error);
}
