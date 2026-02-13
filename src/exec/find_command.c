/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:08:27 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/05 20:30:35 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Checks whether a command given by a path is executable.*/
char	*command_check(char *cmd, int *result)
{
	struct stat	info;
	int			errno;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		errno = 0;
		if (access(cmd, X_OK) != 0 || stat(cmd, &info) != 0)
		{
			if (errno == EACCES)
				*result = -1;
			else if (errno == ENOENT)
				*result = -2;
			return (NULL);
		}
		if (S_ISDIR(info.st_mode))
		{
			*result = -3;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

/* Retrieves and splits the PATH environment variable. */
char	**split_path(t_data *minishell)
{
	char	*path;
	char	**paths;

	path = get_env_value(*minishell->lev, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/* Resolves the absolute path of a command.
Returns the full path if found and executable */
char	*find_command(t_data *minishell, char *cmd, int *result)
{
	char	**paths;
	char	*full_path;
	int		i;

	full_path = command_check(cmd, result);
	if (full_path)
		return (full_path);
	paths = NULL;
	if (*result != 0)
		return (NULL);
	paths = split_path(minishell);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = concatenate(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		deallocate_mem(full_path);
		full_path = NULL;
		i++;
	}
	ft_free_matrix(paths);
	return (full_path);
}
