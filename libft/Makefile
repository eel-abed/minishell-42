# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 09:57:59 by mafourni          #+#    #+#              #
#    Updated: 2024/03/04 14:55:27 by mafourni         ###   ########.fr        #
#
NAME = libft.a

RM = rm -f

SRC = ft_atoi.c ft_putnbr_fd.c ft_putchar_fd.c ft_isascii.c ft_isalpha.c \
	ft_isdigit.c ft_isprint.c  ft_strlen.c ft_strncmp.c ft_strdup.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_toupper.c ft_tolower.c ft_memcpy.c ft_memset.c ft_memmove.c \
	ft_isalnum.c ft_memcmp.c ft_memchr.c ft_strchr.c ft_substr.c ft_bzero.c \
	ft_strrchr.c ft_calloc.c ft_strlcpy.c ft_strnstr.c ft_strlcat.c ft_strjoin.c \
	ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_printf.c \
	ft_print_char.c ft_print_char.c ft_print_format.c \
	ft_print_hexmaj.c ft_print_hexmin.c ft_print_nbr.c \
	ft_print_str.c ft_print_ptr.c ft_print_nbru.c get_next_line.c \
	get_next_line_utils.c ft_lstnew_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c \
	ft_lstiter_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o: %.c
	cc -Wall -Werror -Wextra -g -c $< -o $@ -I.

$(NAME):	$(OBJ)
	ar rcs $@ $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all