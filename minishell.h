/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 11:51:09 by dperez-p          #+#    #+#             */
/*   Updated: 2026/02/07 19:43:33 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_complete/ft_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

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

typedef long long	t_ll;

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

/* MAIN functions */
int		main(int ac, char **av, char **ev);
void	finish(t_data *minishell);
void	update_exit_status(t_data *minishell, int status);

/* Builtin */
int		command_menu(t_data *minishell, char **args);
void	update_env_var(t_lev **lev, char *key, char *value);
int		cd(t_lev **lev, char **args);
int		echo(char **args);
int		env(t_lev **lev, char **args);
int		exec_exit(t_data *minishell, char **args);
void	print_export(t_lev **lev);
void	parse_assignment(char *arg, char **key, char **value, int *append);
int		export(t_data *minishell, char **args);
void	export_variable(t_lev **lev, char *key, char *value, int append);
int		pwd(t_data *minishell);
int		unset(t_data *minishell, char **arg);
t_ll	ft_atoll(const char *str);
int		is_valid_identifier(const char *str);

/* Exec */
int		execute_command(t_data *minishell);
int		loop_tree(t_data *minishell, t_ast *ast);
void	execute_child_command(char *command, char **args, t_data *minishell);
int		execute_parent_command(pid_t pid);
int		execution_route(t_data *minishell, char **args);
char	*find_command(t_data *minishell, char *cmd, int *result);
char	**split_path(t_data *minishell);
char	*command_check(char *cmd, int *result);
int		execute_pipe(t_data *minishell, t_ast *ast);
int		execute_redir(t_data *minishell, t_ast *ast, int id);
int		execute_submodule(t_data *minishell, t_ast *ast);

/* Environtment */
t_lev	*create_env_node(char **arr_ev);
void	append_env_node(t_lev **lev, t_lev *new_node);
char	**separate_ev(char *ev);
t_lev	**init_env_list(t_data *minishell);
t_lev	*findlev(t_lev *lev, const char *key);
char	**convert_lev_to_array(t_data *minishell);
int		remove_env_node(t_lev **lev, char *key);
void	free_env_list(t_lev **lev);

/* Expansion*/
char	**split_tokens(char *expanded);
char	*remove_quotes(char *str);
char	*unquote_dollar(t_data *minishell, char *token, int *i, int *start);
char	*expand_token(t_data *minishell, char *token);
void	free_both(char *a, char *b);
char	*expand_wildcards(char *token);
char	*handle_dollar(t_data *minishell, char *str, int *i);
char	**expansor(t_data *minishell, char **tokens);
char	*get_env_value(t_lev *lev, const char *var_name);
char	**realloc_matches_array(char **matches, const char *new_match,
			int count);
char	*get_key_value(t_lev *lev, const char *key);
char	*ft_strjoin_free(char *s1, char *s2);

/* Init */
t_data	*init_minishell(char **ev);
void	free_minishell(t_data *minishell);

/* Input */
int		check_syntax(t_data *minishell, t_token *token);
char	*get_input(t_data *minishell);
int		check_input_syntax(char *str);
int		check_empty_input(char *str);

/* Parser */
void	remove_heredoc_files(t_data *minishell);
void	parse_heredoc(t_data *minishell, t_token *operator);
t_ast	*parse_redir(t_data *minishell, t_token *token, t_token *operator);
t_ast	*parse_operator(t_data *minishell, t_token *token, t_token *operator);
t_ast	*parse_token(t_token *token);
t_ast	*parse_subshell(t_data *minishell, t_token *token);
t_token	*search_pipeline(t_token *token);
t_token	*find_main_operator(t_token *token);
t_token	*search_redir(t_token *token);
t_token	*remove_outer_parentheses(t_token *token);
int		is_subshell(t_token *token);
t_ast	*new_node(int id);
t_ast	*build_tree(t_data *minishell, t_token *token);
void	free_ast(t_ast *node);
t_token	*split_token_list(t_token *token, t_token *operator);
int		arg_count(t_token *token);

/* Signals */
void	handle_heredoc(int signum);
void	heredoc_signals(void);
void	handle_sigint(int sig);
void	setup_signals(int pid);
void	handle_sigpipe(int signum);
void	handle_ctrl_c(int sig);
void	interactive_signals(void);

/* Tokenizer*/
t_token	*create_token(char *value, int id);
void	add_token(t_token **tokens, t_token *new_token);
void	free_tokens(t_token **tokens);
void	free_token_node(t_token *token);
char	*extract_token(const char *input, int id);
t_token	**tokenize_input(char *input);
int		token_length(const char *str, int id);

/* utils */
void	handle_error(char *error);
int		print_command_error(int res, char *args);
int		print_error(int error, int res_num, char *cmd, char *arg);
char	*concatenate(const char *s1, const char *s2, const char *s3);
void	close_fd(int *fd);
int		skip_zeros(const char *num);
void	restore_fd(int *fd);
void	free_minishell(t_data *minishell);

#endif