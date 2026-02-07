/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:08:05 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 19:22:08 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			result[j++] = str[i];
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
	char	*sub;

	if (end > start)
	{
		sub = ft_substr(expanded, start, end - start);
		tmp = remove_quotes(sub);
		free(sub);
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

/* Helper function to update the current quote state */
char	**split_tokens(char *expanded)
{
	char	**split;
	char	quote;
	int		i;
	int		j;

	split = allocate_mem(1, sizeof(char *));
	j = 0;
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
