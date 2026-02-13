/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:07:45 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/04 11:32:46 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Unsets (removes) environment variables from the minishell's environment list
   based on the provided arguments */
int	unset(t_data *minishell, char **arg)
{
	int	i;

	i = 1;
	while (arg[i] && arg[i][0])
	{
		if (is_valid_identifier(arg[i]))
		{
			if (remove_env_node(minishell->lev, arg[i]) == 0)
				minishell->ev_num--;
		}
		i++;
	}
	return (0);
}
