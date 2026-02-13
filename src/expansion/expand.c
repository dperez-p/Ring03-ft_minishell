/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:59:31 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/08 16:18:59 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Function to expand tilde (~) to home directory */
static char	*expand_tilde(t_data *minishell, char *token)
{
	char	*home;
	char	*expanded;

	expanded = NULL;
	if (token[0] != '~')
		return (token);
	home = get_env_value(*minishell->lev, "HOME");
	if (!home)
		return (token);
	if (token[1] == '\0')
		expanded = ft_strdup(home);
	else if (token[1] == '/')
		expanded = ft_strjoin(home, &token[1]);
	else
		return (token);
	free(token);
	return (expanded);
}

/* Helper function to handle special cases for dollar sign */
static char	*handle_dollar_special_case(t_data *minishell, char curr, int *i)
{
	(*i)++;
	if (curr == '?')
		return (ft_itoa(minishell->status));
	return (NULL);
}

/* Function to handle dollar sign expansion in tokens */
char	*handle_dollar(t_data *minishell, char *str, int *i)
{
	char	*curr;
	char	*var_name;
	char	*var_value;
	char	*result;
	int		len;

	curr = str + 1;
	if (*curr == '?')
		return (handle_dollar_special_case(minishell, *curr, i));
	len = 0;
	while (curr[len] && (ft_isalnum(curr[len]) || curr[len] == '_'))
		len++;
	*i += len;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = malloc((len + 1) * sizeof(char));
	ft_strlcpy(var_name, curr, len + 1);
	var_value = get_env_value(*minishell->lev, var_name);
	if (!var_value)
		result = ft_strdup("");
	else
		result = ft_strdup(var_value);
	free(var_name);
	return (result);
}

/* Expand the user’s tokens (resolving variables, tildes, and wildcards) into a
 new argument array ready to be executed, freeing the original memory */
char	**expansor(t_data *minishell, char **tokens)
{
	char	**args;
	char	**split;
	char	*expanded;
	int		i;
	int		j;

	args = allocate_mem(1, sizeof(char *));
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '#')
			break ;
		expanded = expand_token(minishell, tokens[i]);
		expanded = expand_tilde(minishell, expanded);
		expanded = expand_wildcards(expanded);
		split = split_tokens(expanded);
		free(expanded);
		j = 0;
		while (split[j])
			args = realloc_matches_array(args, split[j++], ft_array_len(args));
		ft_free_matrix(split);
		i++;
	}
	ft_free_matrix(tokens);
	return (args);
}
