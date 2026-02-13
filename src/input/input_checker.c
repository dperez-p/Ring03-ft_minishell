/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 10:51:47 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 18:44:00 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Searches for disallowed characters (\ or ;) outside of quotes in the string
 returns 1 if the string is valid, or 0 if a forbidden character is found */
static int	check_special_chars(char *str)
{
	char	quote;

	quote = '\0';
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = '\0';
		else if (!quote && (*str == '\\' || *str == ';'))
			return (0);
		str++;
	}
	return (1);
}

/* Verifies that all quotes (single or double) have a matching closing pair
 returns 1 if all quotes are closed, or 0 if any remain open */
static int	check_open_quotes(char *str)
{
	int		quotes;
	char	type;

	quotes = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			type = *str;
			quotes++;
			str++;
			while (*str && *str != type)
				str++;
			if (*str == type)
				quotes++;
		}
		if (*str)
			str++;
	}
	if (quotes % 2 != 0)
		return (0);
	return (1);
}

/* Checks that quotes and parentheses are correctly closed
 and balanced returns 1 if everything is properly closed,
 or 0 if there are opening or closing errors */
static int	check_open_syntax(char *str)
{
	int		paren;
	char	quote;

	paren = 0;
	quote = '\0';
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (quote && *str == quote)
			quote = '\0';
		else if (!quote && *str == '(')
			paren++;
		else if (!quote && *str == ')')
		{
			paren--;
			if (paren < 0)
				return (0);
		}
		str++;
	}
	return (paren == 0);
}

/* Checks if the input is empty or contains only whitespace returns 1 
 if there is no executable content, or 0 if a valid character is found */
int	check_empty_input(char *str)
{
	while (*str)
	{
		if (!ft_is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

/* Verifies the initial syntax of the string using opening rules and special
 characters returns 0 if valid, or a syntax error if any check fails */
int	check_input_syntax(char *str)
{
	if (!check_open_quotes(str))
		return (print_error(QUOTES, 2, NULL, NULL));
	if (!check_open_syntax(str))
		return (print_error(SYNTAX, 2, NULL, "newline"));
	if (!check_special_chars(str))
		return (print_error(INVALID_INPUT, 2, str, NULL));
	return (0);
}
