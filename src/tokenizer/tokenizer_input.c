/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:20:17 by dperez-p          #+#    #+#             */
/*   Updated: 2025/12/30 19:30:45 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	**tokenize_input(const char *input)
{
	int		id;
	char	*current_token;
	t_token	**tokens;
	t_token	*new_token;

	tokens = malloc(sizeof(t_token *));
	if (!tokens)
	{
		handle_error(MALLOC);
	}
	*tokens = NULL;
	while (*input)
	{
		while (*input > 9 && *input < 13 || *input == 32 )
			input++;
		if (*input)
		{
			id = extract_token_id(input);
			current_token = extract_token(input, id);
			new_token = create_token(current_token, id);
			add_token(tokens, new_token);
			input += token_length(current_token, id);
		}
	}
	return (tokens);
}