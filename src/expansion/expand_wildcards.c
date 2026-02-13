/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:56:56 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/04 12:13:24 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to convert an array of strings into
	a single space-separated string */
static char	*array_to_string(char **array)
{
	char	*result;
	char	*temp;
	int		i;

	if (!array || !array[0])
		return (ft_strdup(""));
	result = ft_strdup(array[0]);
	i = 1;
	while (array[i])
	{
		temp = result;
		result = concatenate(result, " ", array[i]);
		free(temp);
		i++;
	}
	return (result);
}

/* Function to check if a string matches a wildcard pattern */
static int	wildcard_match(const char *pattern, const char *str)
{
	if (!*pattern)
	{
		if (!*str)
			return (1);
		else
			return (0);
	}
	if (*pattern == '*')
		return (wildcard_match(pattern + 1, str)
			|| (*str && wildcard_match(pattern, str + 1)));
	else if (*pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (0);
}

static char	**get_matching_filenames(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = ft_calloc(1, sizeof(char *));
	if (!matches)
		handle_error(MALLOC);
	count = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (wildcard_match(pattern, entry->d_name))
		{
			matches = realloc_matches_array(matches, entry->d_name, count);
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}

/* Function to sort an array of strings*/
static void	ft_sort_string_array(char **array)
{
	int		i;
	int		j;
	char	*temp;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcasecmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/* Function to expand wildcards in a token */
char	*expand_wildcards(char *token)
{
	char	*expanded;
	char	**matches;

	if (!token || !ft_strchr(token, '*'))
		return (token);
	matches = get_matching_filenames(token);
	if (!ft_array_len(matches))
	{
		ft_free_matrix(matches);
		return (token);
	}
	ft_sort_string_array(matches);
	expanded = array_to_string(matches);
	ft_free_matrix(matches);
	free(token);
	return (expanded);
}
