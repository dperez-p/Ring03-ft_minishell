/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:25:24 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/09 18:59:09 by dperez-p         ###   ########.fr       */
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

char	*unquote_dollar(t_data *minishell, char *token, int *i, int *start)
{
	char	*expanded;
	char	*tmp;
	char	*var_value;

	expanded = ft_strdup("");
	tmp = ft_syvstr(token, *start, *i - *start);
	var_value = handle_dollar(minishell, &token[i], i);

