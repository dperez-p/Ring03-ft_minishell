/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ev_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:09:44 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/13 19:01:21 by dperez-p         ###   ########.fr       */
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

/* Convert the linked list of environment variables to an array of strings */
char	**convert_lev_to_array(t_data *minishell)
{
	t_lev	*current;
	char	**envp;
	int		i;

	if (!minishell)
		return (NULL);
	current = *minishell->lev;
	i = 0;
	envp = malloc(sizeof(char *) * (minishell->ev_num + 1));
	if (!envp)
		handle_error(MALLOC);
	while (current)
	{
		envp[i] = concatenate(current->key, "=", current->value);
		if (!envp[i])
			handle_error(MALLOC);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
