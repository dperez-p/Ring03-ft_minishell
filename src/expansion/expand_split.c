/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:08:05 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/11 13:28:24 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Helper function to update the current quote state */
char	**split_tokens(char *expanded)
{
	char	**split;
	char	quote;
	int		i;
	int		j;

	split = malloc(sizeof(char *) * 1);
	if (!split)
		handle_error(MALLOC);
	i = 0;
	quote = '\0';
	while (expanded[i])
	{
		quote = quote_update(expanded[i], quote);
		if (expanded[i] == ' ' && quote == '\0')
		{
			append_split_token(&split, expanded, j, i);
			while (expanded[i] == ' ')
				i++;
			j = i;
			continue ;
		}
		i++;
	}
	append_split_token(&split, expanded, j, i);
	return (split);
}

/* Function to remove quotes from a string */
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	i = 0;
	j = 0;
	quote = '\0';
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		handle_error(MALLOC);
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && quote == str[i])
			quote = '\0';
		else if ((str[i] == '\"' || str[i] == '\'') && quote == '\0')
			quote = str[i];
		else
			result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	return (result);
}

/* Helper function to append a token segment to the split array */
static void	append_split_token(char ***split, char *expanded, int start,
	int end)
{
	char	*tmp;

	if (end > start)
	{
		tmp = ft_substr(expanded, start, end - start);
		tmp = remove_quotes(tmp);
		*split = realloc_matches_array(*split, tmp, ft_array_len(*split));
		free(tmp);
	}
}

/* Helper function to update the current quote state */
static int	quote_update(char curr, char quote)
{
	if ((curr == '\'' || curr == '\"') && quote == '\0')
		return (curr);
	else if (curr == quote)
		return (0);
	return (quote);
}
