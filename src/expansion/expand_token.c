/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:25:24 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/08 16:03:58 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Helper function to skip over single-quoted sections */
static void	skip_single_quote(const char *line, int *i)
{
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	return ;
}

/* Helper function to expand double-quoted sections */
static char	*expand_double_quotes(t_data *minishell, char *token,
	int *i, int *start)
{
	char	*expanded;
	char	*tmp;
	char	*var_value;

	expanded = ft_strdup("");
	(*i)++;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
		{
			tmp = ft_substr(token, *start, *i - *start);
			var_value = handle_dollar(minishell, &token[*i], i);
			expanded = ft_strjoin_free(ft_strjoin_free(expanded, tmp),
					var_value);
			*start = *i + 1;
		}
		(*i)++;
	}
	return (expanded);
}

/* Function to expand tokens by handling quotes and dollar signs */
char	*unquote_dollar(t_data *minishell, char *token, int *i, int *start)
{
	char	*expanded;
	char	*tmp;
	char	*var_value;

	expanded = ft_strdup("");
	tmp = ft_substr(token, *start, *i - *start);
	var_value = handle_dollar(minishell, &token[*i], i);
	expanded = ft_strjoin_free(ft_strjoin_free(expanded, tmp), var_value);
	*start = *i + 1;
	return (expanded);
}

/* Function to expand tokens, handling quotes and dollar signs */
char	*expand_token(t_data *minishell, char *token)
{
	int		i;
	int		start;
	char	*expanded;
	char	*tmp;

	i = 0;
	start = 0;
	expanded = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '\'')
			skip_single_quote(token, &i);
		else if (token[i] == '\"')
			expanded = ft_strjoin_free(expanded,
					expand_double_quotes(minishell, token, &i, &start));
		else if (token[i] == '$')
			expanded = ft_strjoin_free(expanded,
					unquote_dollar(minishell, token, &i, &start));
		if (token[i])
			i++;
	}
	tmp = ft_substr(token, start, i - start);
	expanded = ft_strjoin_free(expanded, tmp);
	return (expanded);
}

/* Helper function to free two strings */
void	free_both(char *a, char *b)
{
	free(a);
	free(b);
}
