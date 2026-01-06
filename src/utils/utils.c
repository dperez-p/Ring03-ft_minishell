/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:16:06 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/06 19:38:39 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*concatenate(const char *s1, const char *s2, const char *s3)
{
	char	*result1;
	char	*result2;

	result1 = ft_strjoin(s1, s2);
	if (!result1)
		return (NULL);
	result2 = ft_strjoin(result1, s3);
	free(result1);
	if (!result2)
		return (NULL);
	return (result2);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int	is_quote_char(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_parenthesis_char(char c)
{
	return (c == '(' || c == ')');
}

int	is_special_char(char c)
{
	return (is_whitespace(c) || is_operator_char(c)
		|| is_parenthesis_char(c));
}
