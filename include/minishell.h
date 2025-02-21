/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:37 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/21 16:17:02 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// COLORS
# define OK "\033[32mOK\033[0m"
# define ERROR "\033[31mERROR\033[0m"
# define KO "\033[31mKO\033[0m"

# define _POSIX_C_SOURCE 200809L
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// TODO ELIAS:

//- Considerer les implications de l'utilisation d'un global variable pour stocker le numero du signal recu
//- Utiliser une structure de donnees plus appropriee que le type "norm" pour stocker les informations sur les signaux
// << >>
// multiple pipes

extern int g_signal_received; // Remplacez g_exit_status par g_signal_received


typedef enum e_operator_kind
{
	kind_none,
	kind_redir_left,
	kind_redir_right,
	kind_redir_2left,
	kind_redir_2right,
	kind_pipe
}						t_operator_kind;
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;
typedef struct s_env
{
	t_env_var			*vars;
	int					size;
}						t_env;
typedef struct s_tokens
{
	t_operator_kind		type;
	char				*value;
	struct s_tokens		*next;
	struct s_tokens		*prev;
	t_env				*env;
}						t_tokens;





typedef struct s_command
{
	char				*input_file;
	char				*output_file;
	char				*delimiter;
	bool				heredoc_flag;
	char				**cmd1;
	char				**cmd2;
	int					pipefd[2];
	pid_t				pid1;
	pid_t				pid2;
	t_env				*env;
	int exit_status; // Ajout du champ pour le status de sortie
}						t_command;

t_env					*init_env(char **envp);
void					free_env(t_env *env);
bool					is_builtin(char *cmd);
void execute_builtin(char *cmd, t_tokens *tokens, t_command *cmd_info);
void					cd_builtin(t_tokens *tokens, t_env *env, t_command *cmd);
void					pwd_builtin(void);
void					echo_builtin(char **args);
void					env_builtin(t_env *env);
void					exit_builtin(char **args, t_command *cmd);
void					export_builtin(char **args, t_env *env);
int						unset_builtin(char **args, t_env *env, t_command *cmd);
void					execute_command(t_tokens *tokens, t_command *cmd_info);
int						execute_external_command(t_tokens *tokens, t_command *cmd);
int						redirect_input(const char *file);
int						redirect_output(const char *file);
int						redirect_append(const char *file);
int						heredoc(const char *delimiter);
pid_t					fork_and_execute_first(t_command *cmd_info);
pid_t					fork_and_execute_second(t_command *cmd_info);
int						handle_input_redirect(char **args, int i,
							t_command *cmd_info);
int						handle_output_redirect(char **args, int i,
							t_command *cmd_info);
int						handle_append_redirect(char **args, int i,
							t_command *cmd_info);
int						handle_heredoc(char **args, int i, t_command *cmd_info);
void					setup_signals(void);
char					*find_command_path(char *cmd, t_env *env);
void					update_env_vars(t_env *env);
char					**env_to_array(t_env *env);
int						quote_check(char *input);
t_env_var				*find_env_var(t_env *env, const char *key);
void					append_env_var(t_env *env, t_env_var *new_var);
void					handle_export_error(char *arg);
void					execute_pipe_commands(t_command *cmd_info);
void					free_paths(char **paths);
char					*join_path(char *path, char *cmd);

// MAXENCE

// LEXER
char					*any_env(char *input, t_env *env);
t_tokens				*ft_lexer(char *input, t_env *env);
int						quote_check(char *input);

bool					check_syntax(char *input);
bool					is_operator(char ch, t_operator_kind *out_kind);
bool					is_valid_operator(char *str, size_t remain,
							t_operator_kind kind);

bool					is_valid_redir_left(char *string, size_t remaining);
bool					is_valid_redir_right(char *string, size_t remaining);
bool					is_valid_pipe(char *string);

// liked list tokens
void					mini_lstadd_back(t_tokens **lst, t_tokens *new);
void					mini_lstadd_front(t_tokens **lst, t_tokens *new);
t_tokens				*mini_lstlast(t_tokens *lst);
t_tokens				*mini_lstnew(char *value, int kind);
int						mini_lstsize(t_tokens *lst);
// COUNT WORD FOR SPLIT
int						count_tokens(char *input);
int						detect_operator(char c);
// SPLIT MINI
char					**split_mini(char *input);
char					*extract_token(char *input, int *i, int *start);
void					skip_quotes(char *input, int *i, char quote);
void					handle_operator(char *input, int *i);
int						is_empty_token(char *str);

// void remove_empty_tokens(t_tokens **list);
t_tokens				*lets_tokeninze(char *input);
int						check_empty_quotes(char *str, int len);
int						is_empty_or_quoted_empty(char *str);
t_tokens				*ft_trim_all(t_tokens *tokens);

// TRIM
char					*trim_unquoted(char *str);
int						has_empty_quotes_at_start(char *str);
int						is_quote(char c);
char					*remove_outer_quotes(char *str);
int						should_trim_quotes(char *str);
int						has_attached_quotes(char *str);

t_tokens				*token_with_pipe(t_tokens *tokens);

// UTILS
bool					is_space(char *input, int i);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dest, char *src, int i, int j);
char					*might_replace(t_env *env, char *input, int j,
							char *tmp);
char					*ft_strlcat_mini(char *dst, const char *src,
							size_t dstsize);
void					print_tokens(t_tokens *list);
#endif
