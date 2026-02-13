/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlghar <najlghar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:28:37 by najlghar          #+#    #+#             */
/*   Updated: 2026/01/31 11:28:53 by najlghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_lev **lev)
{
	t_lev	*current;

	current = *lev;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

void	parse_assignment(char *arg, char **key, char **value, int *append)
{
	int		i;
	char	*equal_pos;

	*append = 0;
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return ;
	}
	if (equal_pos > arg && *(equal_pos - 1) == '+')
	{
		*append = 1;
		i = equal_pos - arg - 1;
	}
	else
		i = equal_pos - arg;
	*key = ft_substr(arg, 0, i);
	*value = ft_strdup(equal_pos + 1);
}
