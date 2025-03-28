# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 15:39:20 by eel-abed          #+#    #+#              #
#    Updated: 2025/03/13 01:01:43 by eel-abed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft

# Source files
SRC_FILES = main.c \
			main_norm.c \
			mainhelperla.c \
            execution/execution.c \
            execution/execution_utils.c \
			execution/exec_cmd_ext.c \
			execution/execution_big_helper.c \
			execution/execution_big_helper2.c \
			execution/exec_cmd_ext_more.c \
			execution/exec_cmd_ext_utils.c \
			helper_func/redirections.c \
			helper_func/redirections2.c \
			helper_func/redirection_helper.c \
			helper_func/redirection_helper2.c \
			helper_func/redirection_helper3.c \
			helper_func/pipe.c \
			helper_func/pipe_extra.c \
			helper_func/handle_redirections.c \
			helper_func/signals.c\
			helper_func/signal2.c\
			helper_func/env_utils.c\
			helper_func/env_setter.c\
            builtin/cd.c \
            builtin/cd_norm.c \
            builtin/echo.c \
            builtin/env.c \
            builtin/exit.c \
            builtin/export.c \
            builtin/export_utils.c \
            builtin/pwd.c \
            builtin/unset.c \
			parsing/lexer/lexer.c \
			parsing/lexer/lexer2.c \
			parsing/lexer/lexer3.c \
			parsing/lexer/env.c \
			parsing/lexer/syntax.c \
			parsing/lexer/syntax2.c \
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
			parsing/lexer/trim4.c \
			parsing/lexer/token_pipe.c \
			parsing/lexer/token_pipe2.c \
			parsing/lexer/env2.c \

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
