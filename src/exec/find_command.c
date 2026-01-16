/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:08:27 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/16 11:32:10 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Retrieves and splits the PATH environment variable. */
char	**split_path(t_data *minishell)
{
	char	*path;
	char	**paths;

	path = get_env_value(*minishell->lev, "PATH");
	if (!path)
		return (NULL);
	path = ft_split(path, ':');
	if (!path)
		return (NULL);
	return (path);
}

/* Resolves the absolute path of a command.
Returns the full path if found and executable */
char	*find_command(t_data *minishell, char *cmd, int *result)
{
	char	**paths;
	char	*full_path;
	int		i;

	full_path = verify_command(cmd, result); //missing
	if (full_path)
		return (full_path);
	if (*result != 0)
		paths = split_path(minishell);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = concatenate(paths[i], "/", cmd);
		if (acces(full_path, X_OK) == 0)
			break ;
		deallocate_mem(full_path);
		full_path = NULL;
		i++;
	}
	ft_free_matrix(paths);
	return (full_path);
}
