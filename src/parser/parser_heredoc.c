/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:32:20 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/12 12:27:04 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_line(t_data *minishell, char *line)
{
	char	*expanded;
	int		i;
	int		start;

	expanded = ft_strdup("");
	if (!expanded)
		handle_error(MALLOC);
	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '$')
			expanded = unquote_dollar(minishell, line, &i, &start);
		else
		{
			expanded = ft_strjoin(expanded, line[i]);
			if (!expanded)
				handle_error(MALLOC);
			i++;
		}
	}
	free(line);
	return (expanded);
}

/* Helper function to write heredoc input to the given file descriptor */
static void	heredoc_write(t_data *minishell, char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file",
				STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

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

/* Function to remove all heredoc temporary files */
void	remove_heredoc_files(t_data *minishell)
{
	int		i;
	char	*path;

	i = 0;
	while (i < minishell->heredoc_num)
	{
		path = concatenate("heredoc_", ft_itoa(i), ".txt");
		if (path)
		{
			unlink(path);
			free(path);
		}
		i++;
	}
}

/* Function to handle heredoc input and write to the specified
	file descriptor */
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
