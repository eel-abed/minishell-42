# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 17:31:31 by codespace         #+#    #+#              #
#    Updated: 2024/09/11 17:48:56 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishel

CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

# SRC
SRC = test.c
OBJ = $(SRC:.c=.o)

# LIB
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# HEADERS
HEADERS_LIB = $(LIBFT_DIR)

all : $(LIBFT_LIB) $(NAME)

$(LIBRD):
	curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz
	tar -zxvf $(LIBRLINE).tar.gz
	@rm -rf $(LIBRLINE).tar.gz
	@cd $(LIBRLINE) && bash configure && make
	@mkdir -p $(LIBRLINE_DIR)/bin
	@mv ./$(LIBRLINE)/*.h $(LIBRLINE_DIR)
	@mv ./$(LIBRLINE)/*.a $(LIBRLINE_DIR)/bin
	@rm -rf $(LIBRLINE)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

%.o: %.c
	gcc $(CFLAGS) -I. -I$(HEADERS_LIB) -c $< -o $@ 

$(NAME): $(OBJ) ${LIBRD}
	 	gcc  $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
		@echo "Compilation terminé avec succès!"


leaks:
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --suppressions=./$(NAME).sup ./$(NAME)

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean 

re: fclean all