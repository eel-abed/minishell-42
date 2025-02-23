# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:39:20 by eel-abed          #+#    #+#              #
#    Updated: 2025/02/23 21:57:40 by mafourni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft

# Source files
SRC_FILES = main.c \
            execution/execution.c \
            execution/execution_utils.c \
			execution/exec_cmd_ext.c \
			execution/exec_cmd_ext_utils.c \
			helper_func/redirections.c \
			helper_func/pipe.c \
			helper_func/handle_redirections.c \
			helper_func/signals.c\
			helper_func/env_utils.c\
            builtin/cd.c \
            builtin/echo.c \
            builtin/env.c \
            builtin/exit.c \
            builtin/export.c \
            builtin/export_utils.c \
            builtin/pwd.c \
            builtin/unset.c \
			parsing/lexer/lexer.c \
			parsing/lexer/syntax.c \
			parsing/lexer/quote.c \
			parsing/utils/utils.c \
			parsing/utils/utils2.c \
			parsing/lexer/linked_listfunctions.c \
			parsing/lexer/token.c \
			parsing/lexer/token2.c \
			parsing/lexer/split.c \
			parsing/lexer/trim.c \
			parsing/lexer/trim2.c \
			parsing/lexer/trim3.c \
			parsing/lexer/token_pipe.c \


# Object files
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Executable name
NAME = minishell

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Includes
INC = -I$(INC_DIR) -I$(LIBFT_DIR)

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
