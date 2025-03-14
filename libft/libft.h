/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:28:36 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 15:28:51 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
// # include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_list
{
	int					content;
	struct s_list		*next;
	int					index;
	bool				flag;
}						t_list;

int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size, t_garbage **gc);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *s, int c, size_t n);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s1, t_garbage **gc);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char					*ft_strrchr(const char *s, int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len, t_garbage **gc);
char					*ft_strjoin(char const *s1, char const *s2,
							t_garbage **gc);
char					*ft_strtrim(char const *s1, char const *set,
							t_garbage **gc);
char					**ft_split(char const *s, char c, t_garbage **gc);
char					*ft_itoa(int n, t_garbage **gc);
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(const char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putendl_fd(char *s, int fd);
t_list					*ft_lstnew(int content);
void					ft_lstadd_front(t_list **lst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **lst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void(*)));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
char					*ft_strncpy(char *dest, char *src, unsigned int n);

void					*gc_malloc(t_garbage **gc, size_t size);

void					gc_free_all(t_garbage **gc);
#endif
