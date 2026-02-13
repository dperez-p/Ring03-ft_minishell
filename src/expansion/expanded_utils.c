/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 09:54:54 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/06 18:45:33 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Expand env value */
char	*get_env_value(t_lev *lev, const char *var_name)
{
	t_lev	*env_var;

	env_var = findlev(lev, var_name);
	if (!env_var || !env_var->value)
		return (NULL);
	return (env_var->value);
}

/* Function to reallocate matches array with a new match */
char	**realloc_matches_array(char **matches, const char *new_match,
	int count)
{
	char	**new_array;
	int		i;

	new_array = allocate_mem(count + 2, sizeof(char *));
	i = 0;
	while (i < count)
	{
		new_array[i] = matches[i];
		i++;
	}
	new_array[i] = ft_strdup(new_match);
	new_array[i + 1] = NULL;
	if (matches)
		free(matches);
	return (new_array);
}

/* Searches for a key in the environment list */
char	*get_key_value(t_lev *lev, const char *key)
{
	t_lev	*env_var;

	env_var = findlev(lev, key);
	if (!env_var || !env_var->value)
		return (NULL);
	return (env_var->value);
}

/* Joins two strings and frees both */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		deallocate_mem(s1);
	if (s2)
		deallocate_mem(s2);
	return (result);
}
