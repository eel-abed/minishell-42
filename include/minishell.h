/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:37 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/10 18:12:24 by eel-abed         ###   ########.fr       */
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

// TODO :

//- Considerer les implications de l'utilisation d'un global variable pour stocker le numero du signal recu
//- Utiliser une structure de donnees plus appropriee que le type "norm" pour stocker les informations sur les signaux
// << >> 
//multiple pipes

extern int				g_exit_status;

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
}						t_command;

t_env					*init_env(char **envp);
void					free_env(t_env *env);
bool					is_builtin(char *cmd);
void					execute_builtin(char *cmd, char **args,
							t_command *cmd_info);
void					cd_builtin(char **args, t_env *env);
void					pwd_builtin(void);
void					echo_builtin(char **args);
void					env_builtin(t_env *env);
void					exit_builtin(char **args);
void					export_builtin(char **args, t_env *env);
int						unset_builtin(char **args, t_env *env);
void					execute_command(char **args, t_command *cmd_info);
int						execute_external_command(char **args, t_command *cmd);
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
t_list					*ft_lexer(char *input);

// MAXENCE

typedef enum e_operator_kind
{
	kind_none,
	kind_redir_left,
	kind_redir_right,
	kind_pipe
}						t_operator_kind;

// LEXER
t_list					*ft_lexer(char *input);
int						quote_check(char *input);

bool					check_syntax(char *input);
bool					is_operator(char ch, t_operator_kind *out_kind);
bool					is_valid_operator(char *str, size_t remain,
							t_operator_kind kind);

bool					is_valid_redir_left(char *string, size_t remaining);
bool					is_valid_redir_right(char *string, size_t remaining);
bool					is_valid_pipe(char *string);

// UTILS
bool					is_space(char *input, int i);

#endif
