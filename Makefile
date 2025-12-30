# Name
NAME	=		minishell

# Compiler and Cflags
CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra
RM		=		rm -f

# Directories
SRC_DIR	=		src/
OBJ_DIR	=		obj/

# SRC files
SRC		=		main.c\
				user_input.c\
				display_prompt.c\
				./command/execute_command.c\
				

SRCS	=		$(addprefix $(SRC_DIR), $(SRC))

# Obj_files
OBJ		=		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# Build rules

all:	$(NAME)

$(NAME):		$(OBJ)
				@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) -r $(OBJ_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re