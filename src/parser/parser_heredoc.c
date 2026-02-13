/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:32:20 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/08 15:34:08 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_line(t_data *minishell, char *line)
{
	int		i;
	int		start;
	char	*expanded;
	char	*temp;

	i = 0;
	start = 0;
	expanded = ft_strdup("");
	while (line [i])
	{
		if (line[i] == '$')
			expanded = ft_strjoin_free(expanded,
					unquote_dollar(minishell, line, &i, &start));
		if (line[i])
			i++;
	}
	temp = ft_substr(line, start, i - start);
	expanded = ft_strjoin_free(expanded, temp);
	free (line);
	return (expanded);
}

/* Helper function to write heredoc input to the given file descriptor */
static void	heredoc_write(t_data *minishell, char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line && g_signal == SIGINT)
		{
			free(line);
			return ;
		}
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			if (!line)
				ft_printf_fd(2,
					"warning: heredoc delimited by end-of-file (wanted `%s')\n",
					delimiter);
			free(line);
			break ;
		}
		line = expand_line(minishell, line);
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
	char	*num;

	i = 0;
	while (i < minishell->heredoc_num)
	{
		num = ft_itoa(i);
		path = concatenate("heredoc_", num, ".txt");
		free(num);
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
	char	*temp;
	int		fd;

	path = get_heredoc_path(minishell);
	if (!path)
		handle_error(MALLOC);
	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		handle_error(TEMP_ERR);
	heredoc_signals();
	temp = operator->next->value;
	operator->next->value = remove_quotes(temp);
	free(temp);
	if (!operator->next->value)
		handle_error(MALLOC);
	heredoc_write(minishell, operator->next->value, fd);
	close(fd);
	interactive_signals();
	dup2(minishell->fd_bk[0], STDIN_FILENO);
	free(operator->next->value);
	operator->next->value = path;
	return ;
}
