/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:09:44 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/28 13:35:41 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to find an environment variable by key in the linked list */
t_lev	*findlev(t_lev *lev, const char *key)
{
	while (lev)
	{
		if (ft_strcmp(lev->key, key) == 0)
			return (lev);
		lev = lev->next;
	}
	return (NULL);
}

/* Converts the linked list of environment variables into a string array
(char **) unifying each key and value with an '=' so the system
can execute them. */
char	**convert_lev_to_array(t_data *minishell)
{
	t_lev	*node;
	char	**array;
	int		i;

	if (!minishell)
		return (NULL);
	node = *minishell->lev;
	i = 0;
	array = allocate_mem((minishell->ev_num + 1), sizeof(char *));
	if (!array)
		handle_error(MALLOC);
	while (node)
	{
		array[i] = concatenate(node->key, "=", node->value);
		i++;
		node = node->next;
	}
	return (array);
}
