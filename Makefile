# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxencefournier <maxencefournier@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 17:31:31 by codespace         #+#    #+#              #
#    Updated: 2024/09/14 19:25:02 by maxencefour      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

# SRC
SRC = main.c
OBJ = $(SRC:.c=.o)

# LIB
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# HEADERS
HEADERS_LIB = $(LIBFT_DIR)

 #READLINE
 
 READLINE_VERSION = readline-8.2
 READLINE_DIR = $(CURDIR)/headers/readline

all : $(LIBFT_LIB) $(READLINE_DIR) $(NAME)

$(READLINE_DIR):
	curl -O https://ftp.gnu.org/gnu/readline/$(READLINE_VERSION).tar.gz
	tar -zxvf $(READLINE_VERSION).tar.gz
	@rm -rf $(READLINE_VERSION).tar.gz
	@cd $(READLINE_VERSION) && ./configure --prefix=$(READLINE_DIR) && make && make install
	@rm -rf $(READLINE_VERSION)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

%.o: %.c
	gcc $(CFLAGS) -I. -I$(HEADERS_LIB) -I$(READLINE_DIR)/include -c $< -o $@

$(NAME): $(OBJ) $(READLINE_DIR)
	 	gcc $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(READLINE_DIR)/lib -lreadline -o $(NAME)
		@echo "Compilation terminé avec succès!"


leaks:
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=./$(NAME).sup ./$(NAME)

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean 
	@rm -rf $(READLINE_DIR)

re: fclean all