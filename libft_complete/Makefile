# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 10:02:35 by dperez-p          #+#    #+#              #
#    Updated: 2026/02/04 13:23:52 by dperez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRC

NAME = libft.a
INC = inc/
FT_LIBFT = ./ft_libft/ft_isalnum.c ./ft_libft/ft_isalpha.c ./ft_libft/ft_isascii.c ./ft_libft/ft_isdigit.c ./ft_libft/ft_isprint.c \
		./ft_libft/ft_strlen.c ./ft_libft/ft_memset.c ./ft_libft/ft_bzero.c ./ft_libft/ft_memcpy.c ./ft_libft/ft_memmove.c \
		./ft_libft/ft_strlcpy.c ./ft_libft/ft_strlcat.c ./ft_libft/ft_toupper.c ./ft_libft/ft_tolower.c ./ft_libft/ft_strchr.c \
		./ft_libft/ft_strrchr.c ./ft_libft/ft_memchr.c ./ft_libft/ft_strncmp.c ./ft_libft/ft_memcmp.c ./ft_libft/ft_strnstr.c \
		./ft_libft/ft_atoi.c ./ft_libft/ft_calloc.c ./ft_libft/ft_substr.c ./ft_libft/ft_strdup.c ./ft_libft/ft_strtrim.c \
		./ft_libft/ft_strjoin.c ./ft_libft/ft_split.c ./ft_libft/ft_itoa.c ./ft_libft/ft_putchar_fd.c ./ft_libft/ft_putnbr_fd.c \
		./ft_libft/ft_putstr_fd.c ./ft_libft/ft_putendl_fd.c ./ft_libft/ft_striteri.c ./ft_libft/ft_strmapi.c \
		./ft_libft/ft_lstnew_bonus.c ./ft_libft/ft_lstadd_front_bonus.c ./ft_libft/ft_lstsize_bonus.c \
		./ft_libft/ft_lstlast_bonus.c ./ft_libft/ft_lstadd_back_bonus.c ./ft_libft/ft_lstdelone_bonus.c \
		./ft_libft/ft_lstclear_bonus.c ./ft_libft/ft_lstiter_bonus.c ./ft_libft/ft_lstmap_bonus.c ./ft_libft/ft_free_matrix.c \
		./ft_libft/ft_array_len.c ./ft_libft/ft_strcasecmp.c ./ft_libft/ft_memory_collect.c ./ft_libft/ft_is_space.c \
		./ft_libft/ft_print_fd.c

FT_PRINTF = ./ft_printf/ft_printf.c ./ft_printf/ft_putchar.c ./ft_printf/ft_putstr.c ./ft_printf/ft_putnbr.c \
		./ft_printf/ft_print_unsigned.c ./ft_printf/ft_print_hex.c ./ft_printf/ft_print_ptr.c

FT_GET_NEXT_LINE = ./ft_get_next_line/get_next_line.c ./ft_get_next_line/get_next_line_utils.c

SRC = $(FT_LIBFT) $(FT_PRINTF) $(FT_GET_NEXT_LINE)

OFILES = $(SRC:.c=.o)

# Commands

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

# Build rules

all: $(NAME)

$(NAME): $(OFILES)
	@$(AR) -r $@ $^

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
