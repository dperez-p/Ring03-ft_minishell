/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_syntax_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:37:54 by dperez-p          #+#    #+#             */
/*   Updated: 2025/12/30 19:16:03 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Check for unclosed quotes in the input */
static int	check_open_quotes(const char *input)
{
	char	i;

	i = '\0';
	while (*input)
	{
		if (!i && (*input == '\'' || *input == '\"'))
			i = *input;
		else if (i && *input == i)
			i = '\0';
		input++;
	}
	if (i)
		return (0);
	return (1);
}

/* Check for unclosed quotes in the input */
static int	check_open_syntax(const char *input)
{
	char	i;
	int		parentheses;

	i = '\0';
	parentheses = 0;
	while (*input)
	{
		if (!i && (*input == '\'' || *input == '\"'))
			i = *input;
		else if (i && *input == i)
			i = '\0';
		else if (!i && *input == '(')
			parentheses++;
		else if (!i && *input == ')')
		{
			parentheses--;
			if (parentheses < 0)
				return (0);
		}
		input++;
	}
	return (parentheses == 0 && !i);
}

/* Check for special characters at invalid positions */
static int	check_special_chars(const char *input)
{
	char	i;

	i = '\0';
	while (input[i])
	{
		if (!i && (*input == '\'' || *input == '\"'))
			i = *input;
		else if (i && *input == i)
			i = '\0';
		else if (!i && (*input == '\\' || *input == ';'))
			return (0);
		i++;
	}
	return (1);
}

/* Check if the input is empty*/
int	check_empy_input(const char *input)
{
	while (*input)
	{
		if ((input >= 9 && *input <= 13) || *input == 32)
			return (0);
		input++;
	}
	return (1);
}

/* Check the overall syntax of the input */
int	check_syntax(const char *input)
{
	if (!check_open_syntax(input) || !check_special_chars(input))
		return (print_error(SYNTAX, 2, NULL, NULL));
	return (0);
}
