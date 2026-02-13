/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:20:17 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 18:17:10 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Extracts the token ID from the input string */
static int	get_id(const char *token)
{
	if (token[0] == '&' && token[1] == '&')
		return (AND);
	else if (token[0] == '|' && token[1] == '|')
		return (OR);
	else if (token[0] == '|')
		return (PIPE);
	else if (token[0] == '<' && token[1] == '<')
		return (HEREDOC);
	else if (token[0] == '>' && token[1] == '>')
		return (APPEND);
	else if (token[0] == '<')
		return (REDIR_IN);
	else if (token[0] == '>')
		return (REDIR_OUT);
	else if (token[0] == '(')
		return (PAREN_OPEN);
	else if (token[0] == ')')
		return (PAREN_CLOSE);
	else
		return (ARG);
}

/* Extracts the token string from the input based on its type */
char	*extract_token(const char *input, int id)
{
	int		len;
	char	*token;
	int		i;

	len = token_length(input, id);
	token = malloc((len + 1) * sizeof(char));
	if (!token)
		handle_error(MALLOC);
	i = 0;
	while (i < len)
	{
		token[i] = input[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

/*Calculates the length of the current token based on its type and quoting rules
 returns a fixed size for operators or a dynamic size for arguments (ARG) */
int	token_length(const char *str, int id)
{
	int		len;
	char	quote;

	len = 0;
	quote = '\0';
	if (id == PIPE || id == PAREN_OPEN || id == PAREN_CLOSE || id == REDIR_IN
		|| id == REDIR_OUT)
		return (1);
	if (id == AND || id == OR || id == APPEND || id == HEREDOC)
		return (2);
	while (str[len] && !ft_is_space(str[len]) && (get_id(&str[len]) == ARG))
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			quote = str[len];
			len++;
			while (str[len] && str[len] != quote)
				len++;
			if (str[len] == quote)
				len++;
		}
		else
			len++;
	}
	return (len);
}

/* Tokenizes the input string into a linked list of tokens*/
t_token	**tokenize_input(char *input)
{
	int		id;
	char	*current_token;
	t_token	**tokens;
	t_token	*new_token;

	tokens = malloc(sizeof(t_token *));
	if (!tokens)
		handle_error(MALLOC);
	*tokens = NULL;
	while (*input)
	{
		while (*input && ft_is_space(*input))
			input++;
		if (*input)
		{
			id = get_id(input);
			current_token = extract_token(input, id);
			new_token = create_token(current_token, id);
			add_token(tokens, new_token);
			input += token_length(current_token, id);
		}
	}
	return (tokens);
}
