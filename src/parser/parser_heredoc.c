/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:32:20 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/06 19:47:54 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Helper function to generate a unique heredoc file path */
static char	*get_heredoc_path(t_data *minishell)
{
	char	*path;
	char	*num_str;

	num_str = ft_itoa(minishell->heredoc_num);
	if (!num_str)
		handle_error(MALLOC);
	path = concatenate("heredoc_", num_str, ".txt");
	free(num_str);
	if (!path)
		handle_error(MALLOC);
	minishell->heredoc_num++;
	return (path);
}

void	parse_heredoc(t_data *minishell, t_token *operator)
{
	char	*path;
	int		fd;

	path = get_heredoc_path(minishell);
	if (!path)
		handle_error(MALLOC);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		handle_error(OPEN);
	heredoc_signaals();
	operator->next->value = remove_quotes(operator->next->value);
	if (!operator->next->value)
		handle_error(MALLOC);
	heredoc_write(minishell, operator->next->value, fd);
	close(fd);
	interactive_signals();
	dup2(minishell->fd_bk[0], STDIN_FILENO);
	free(operator->next->value);
	operator->next->value = ft_strdup(path);
	return ;
}