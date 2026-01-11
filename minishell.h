/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:51:09 by dperez-p          #+#    #+#             */
/*   Updated: 2026/01/11 19:54:15 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft_complete/ft_libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*GLOBAL*/
extern volatile int	g_signal;

/* MACROS*/
# define USAGE "Usage: ./minishell"
# define INPUT "Error: When reading input"
# define EV "Error: Could not allocate memory to environment variables"
# define MALLOC "Error: When using malloc"
# define BUILTIN "Error: In Builtin function"
# define EV_NOTFOUND "Error: Could not find environment variables"
# define FORK "Error: Failed to fork process"
# define PIPE_ERR "Error: Failed to create pipe"
# define DUP_ERR "Error: Failed to duplicate file descriptor"
# define TEMP_ERR "Error: Failed to create/open temporary file"
# define SIGNAL "Error: Failed to set signal handler"

# define INVALID_OPTION 1
# define INVALID_ARG 2
# define INVALID_ID 3
# define NUMERIC_ARG 4
# define EXCEED_ARG 5
# define INVALID_FILE 6
# define INVALID_PATH 7
# define INVALID_CMD 8
# define EXECVE 9
# define INVALID_INPUT 10
# define QUOTES 11
# define SYNTAX 12
# define DIR_CMD 13
# define INVALID_PERM 14
# define AMBIGUOUS_REDIR 15
# define FALSE 0
# define TRUE 1

# define YELLOW  "\001\033[0;33m\002"
# define RESET   "\001\033[0m\002"


/******************************************* STRUCTS ********************/

/* Token IDs */
typedef enum s_id
{
	NONE,
	AND,
	OR,	
	PIPE,
	PAREN_OPEN,
	PAREN_CLOSE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	ARG,
	SUBSHELL
}	t_id;

/* Linked list for environment variables */
typedef struct s_lev
{
	char			*key;
	char			*value;
	struct s_lev	*prev;
	struct s_lev	*next;
}	t_lev;

/* Token */
typedef struct s_token
{
	int				id;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/* Abstract Syntax Tree */
typedef struct s_ast
{
	int				id;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

/* File descriptor list */
typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}	t_fd_list;

/* Main data structure for minishell */
typedef struct s_data
{
	char		*input;
	const char	*prompt;
	int			status;
	int			ev_num;
	int			fd_bk[2];
	int			heredoc_num;
	char		**ev;
	t_lev		**lev;
	t_token		**token;
	t_ast		**ast;
}	t_data;

/* SRC functions */
char	*get_input(t_data *minishell);
int		check_empty_input(const char *input);
void	iteration_init(t_data *minishell);
void	update_exit_status(t_data *minishell, int status);
void	finish(t_data *minishell);

/* Checkers */
int		check_open_quotes(const char *input);
int		check_open_syntax(const char *input);
int		check_special_chars(const char *input);
int		check_empty_input(const char *input);
int		check_syntax(const char *input);

/* utils */
char	*concatenate(const char *s1, const char *s2, const char *s3);
void	close_fd(int *fd);
int		skip_zeros(const char *num);
void	handle_error(char *error);
int		print_command_error(int res, char *args);
int		print_error(int error, int res_num, char *cmd, char *arg);

/* Parser*/
t_ast	*parse_tokens(t_data *minishell, t_token *token);
int		is_subshell(t_token *token);
t_token	*find_main_operator(t_token *token);
t_token	*remove_outer_parentheses(t_token *token);
t_ast	*parse_subshell(t_data *minishell, t_token *token);
t_ast	*parse_operator(t_data *minishell, t_token *token, t_token *operator);
t_token	*search_pipeline(t_token *token);
t_ast	*parse_token(t_token *token);
t_ast	*build_tree(t_data *minishell, t_token *token);
t_ast	*new_node(int id);
t_ast	*parse_redir(t_data *minishell, t_token *token, t_token *operator);
void	parse_heredoc(t_data *minishell, t_token *operator);
void	remove_heredoc_files(t_data *minishell);

/* Expansion*/
char	*expand_token(t_data *minishell, char *token);
char	*handle_dollar(t_data *minishell, char *str, int *i);
char	*expand_tilde(t_data *minishell, char *token);
char	*get_env_value(t_list *lev, const char *var_name);
void	free_both(char *a, char *b);
char	**realloc_matches_array(char **matches, const char *new_match,
			int count);
void	ft_sort_string_array(char **array);
char	*expand_wildcards(char *token);
char	*array_to_string(char **array);
char	**expansor(t_data *minishell, char **tokens);
char	**split_tokens(char *expanded);
char	*remove_quotes(char *str);


/* Signals */
void	handle_heredoc(int signum);
void	handle_sigint(void);

/* ev */
t_lev	*findlev(t_lev *lev, const char *key);
t_lev	*create_env_node(char **arr_ev)
t_lev	**init_env_list(t_data *minishell);
char	**separate_ev(char *ev);
void	append_env_node(t_lev **lev, t_lev *new_node);


#endif