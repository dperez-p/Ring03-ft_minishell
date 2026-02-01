/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlghar <najlghar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:27:00 by najlghar          #+#    #+#             */
/*   Updated: 2026/01/31 11:27:33 by najlghar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	create_new_env_var(t_lev **lev, char *key, char *value)
{
	char	*arr_ev[3];
	t_lev	*new_node;

	arr_ev[0] = key;
	arr_ev[1] = value;
	arr_ev[2] = NULL;
	new_node = create_env_node(arr_ev);
	append_env_node(lev, new_node);
}

void	update_env_var(t_lev **lev, char *key, char *value)
{
	t_lev	*node;
	char	*new_value;

	node = findlev(*lev, key);
	if (node)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			handle_error(MALLOC);
		free(node->value);
		node->value = new_value;
	}
	else
		create_new_env_var(lev, key, value);
}
