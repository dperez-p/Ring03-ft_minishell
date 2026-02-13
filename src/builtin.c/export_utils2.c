/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:29:53 by najlghar          #+#    #+#             */
/*   Updated: 2026/02/01 13:05:30 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_existing_var(t_lev *node, char *value, int append)
{
	char	*new_value;

	if (!value)
		return ;
	if (append && node->value)
	{
		new_value = ft_strjoin(node->value, value);
		free(node->value);
		node->value = new_value;
	}
	else
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
}

static void	create_new_var(t_lev **lev, char *key, char *value)
{
	char	*arr_ev[3];
	t_lev	*new_node;

	arr_ev[0] = key;
	if (value)
		arr_ev[1] = value;
	else
		arr_ev[1] = NULL;
	arr_ev[2] = NULL;
	new_node = create_env_node(arr_ev);
	append_env_node(lev, new_node);
}

void	export_variable(t_lev **lev, char *key, char *value, int append)
{
	t_lev	*node;

	node = findlev(*lev, key);
	if (node)
		update_existing_var(node, value, append);
	else
		create_new_var(lev, key, value);
}
