/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:25:24 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/08 19:05:27 by dperez-p         ###   ########.fr       */
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

/* Function to expand variables in a line */
char	*expand_variable(t_data *minishell, const char *line, int *i,
	char *expanded)
{
	char	*var_name;
	char	*var_value;
	int		start;


}
