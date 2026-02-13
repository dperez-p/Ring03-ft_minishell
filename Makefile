# Name
NAME	=		minishell

# Compiler and flags
CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra
RM		=		rm -f
LIBS	=		-lreadline

# Directories
SRC_DIR	=		src/
OBJ_DIR	=		obj/

# Libft
LIBFT_DIR	=	./libft_complete
LIBFT		=	$(LIBFT_DIR)/libft.a

# SRC files
SRC		=	main.c \
			builtin.c/builtin.c \
			builtin.c/cd_utils.c \
			builtin.c/cd.c \
			builtin.c/echo.c \
			builtin.c/env.c \
			builtin.c/exit_utils.c \
			builtin.c/exit.c \
			builtin.c/export_utils.c \
			builtin.c/export_utils2.c \
			builtin.c/export.c \
			builtin.c/pwd.c \
			builtin.c/unset.c \
			environment/env_init.c \
			environment/env_utils.c \
			exec/execute_redir.c \
			exec/execution_pipe.c \
			exec/execution_route.c \
			exec/execution_submodule.c \
			exec/execution.c \
			exec/find_command.c \
			expansion/expand_split.c \
			expansion/expand_token.c \
			expansion/expand_wildcards.c \
			expansion/expand.c \
			expansion/expanded_utils.c \
			init/init.c \
			input/input_checker.c \
			input/input_syntax_check.c \
			input/input.c \
			parser/parser_heredoc.c \
			parser/parser_operators.c \
			parser/parser_search.c \
			parser/parser_utils.c \
			parser/parser.c \
			signals.c/handle_signals.c \
			signals.c/signals.c \
			tokenizer/token_utils.c \
			tokenizer/tokenizer_input.c \
			utils/handle_errors.c \
			utils/utils.c \
			utils/free_minishell.c

SRCS	=		$(addprefix $(SRC_DIR), $(SRC))

# Obj_files
OBJ		=		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Build rules

all:	$(NAME)

$(NAME):		$(OBJ) $(LIBFT)
				@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR)

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@make -C $(LIBFT_DIR) clean
				@$(RM) -r $(OBJ_DIR)

fclean:			clean
				@make -C $(LIBFT_DIR) fclean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft