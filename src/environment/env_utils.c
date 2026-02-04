/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:09:44 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 11:41:03 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to find an environment variable by key in the linked list */
t_lev	*findlev(t_lev *lev, const char *key)
{
	int	len;

	len = ft_strlen(key);
	if (!lev)
		return (0);
	while (lev)
	{
		if (!ft_strncmp(lev->key, key, len + 1))
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

/* Searches for a node by key, unlinks it from the doubly linked list 
   by updating neighbor pointers, and frees its allocated memory */
int	remove_env_node(t_lev **lev, char *key)
{
	t_lev	*node;

	node = findlev(*lev, key);
	if (!node)
		return (1);
	if (*lev == node)
		*lev = node->next;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	deallocate_mem(node->key);
	deallocate_mem(node->value);
	deallocate_mem(node);
	return (0);
}
