/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:37 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/06 17:22:58 by mafourni         ###   ########.fr       */
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

typedef struct s_quote_params
{
	char	*str;
	int		*i;
	int		*j;
	char	quote;
	char	*result;
}	t_quote_params;

typedef struct s_range
{
	int	start;
	int	end;
}	t_range;

extern int				g_signal_received;

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
	int					exit_status;
}						t_command;

typedef struct s_pipe_data
{
	int					i;
	int					pipe_count;
	int					cmd_count;
	int					**pipes;
	pid_t				*pids;
	t_tokens			*current;
	t_command			*cmd_info;
	t_garbage			**gc;
}						t_pipe_data;

t_env					*init_env(char **envp, t_garbage **gc);
void					free_env(t_env *env);
bool					is_builtin(char *cmd);
void					execute_builtin(char *cmd, t_tokens *tokens,
							t_command *cmd_info, t_garbage **gc);
void					cd_builtin(t_tokens *tokens, t_env *env, t_command *cmd,
							t_garbage **gc);
void					pwd_builtin(void);
void					echo_builtin_tokens(t_tokens *tokens);
bool					handle_redirection_tokens(t_tokens *tokens, t_command *cmd_info, t_garbage **gc);
void					env_builtin(t_env *env);
void					exit_builtin(t_tokens *tokens, t_command *cmd,
							t_garbage **gc);
void					export_builtin(t_tokens *tokens, t_env *env,
							t_garbage **gc, t_command *cmd);
int						unset_builtin(t_tokens *tokens, t_env *env,
							t_command *cmd, t_garbage **gc);
void					execute_command(t_tokens *tokens, t_command *cmd_info,
							t_garbage **gc);
int						execute_external_command(t_tokens *tokens,
							t_command *cmd, t_garbage **gc);
int						redirect_output(const char *filename, int append_mode);
int						redirect_input(const char *filename);
int						count_commands(t_tokens *tokens);
int						setup_pipes(int **pipes, int pipe_count);
void					close_all_pipes(int **pipes, int pipe_count);
void					child_process(t_pipe_data *data);
void					wait_for_children(pid_t *pids, int cmd_count,
							t_command *cmd_info);
t_tokens				*find_next_command(t_tokens *current);
int						heredoc(const char *delimiter, t_garbage **gc);
bool					handle_redirectionnn(char **parts, t_command *cmd_info,
							t_garbage **gc);
int						handle_command_not_found(char *cmd);
void					execute_piped_commands(t_tokens *tokens,
							t_command *cmd_info, t_garbage **gc);
void					execute_child(char *cmd_path, char **cmd_args,
							char **env_array);
void					setup_signals(void);
char	*replace_substring(char *str, t_range pos, char *replacement,
	t_garbage **gc);
char					*find_command_path(char *cmd, t_env *env,
							t_garbage **gc);
void					update_env_vars(t_env *env, t_garbage **gc);
char					**env_to_array(t_env *env, t_garbage **gc);
t_env_var				*find_env_var(t_env *env, const char *key);
void					append_env_var(t_env *env, t_env_var *new_var);
void					handle_export_error(char *arg, t_garbage **gc);
char					*join_path(char *path, char *cmd, t_garbage **gc);
char					*any_env(char *input, t_env *env, t_garbage **gc,
							t_command *cmd);
t_tokens				*ft_lexer(char *input, t_env *env, t_garbage **gc,
							t_command *cmd);
int						quote_check(char *input, t_command *cmd);
bool					check_syntax(char *input, t_command *cmd);
bool					is_operator(char ch, t_operator_kind *out_kind);
bool					is_valid_operator(char *str, size_t remain,
							t_operator_kind kind);
bool					is_valid_redir_left(char *string, size_t remaining);
bool					is_valid_redir_right(char *string, size_t remaining);
bool					is_valid_pipe(char *string);
void					mini_lstadd_back(t_tokens **lst, t_tokens *new);
void					mini_lstadd_front(t_tokens **lst, t_tokens *new);
t_tokens				*mini_lstlast(t_tokens *lst);
t_tokens				*mini_lstnew(char *value, int kind, t_garbage **gc);
int						mini_lstsize(t_tokens *lst);
int						count_tokens(char *input);
int						detect_operator(char c);
char					**split_mini(char *input, t_garbage **gc);
char					*extract_token(char *input, int *i, int *start,
							t_garbage **gc);
void					skip_quotes(char *input, int *i, char quote);
void					handle_operator(char *input, int *i);
int						is_empty_token(char *str);
void					handle_quotes(char *input, int *i);
void					process_token(char *input, int *i);
t_tokens				*lets_tokeninze(char *input, t_garbage **gc);
int						check_empty_quotes(char *str, int len);
int						is_empty_or_quoted_empty(char *str);
t_tokens				*ft_trim_all(t_tokens *tokens, t_garbage **gc);
int						should_preserve_token(t_tokens *token);
void					remove_empty_head(t_tokens **list);
char					*trim_unquoted(char *str, t_garbage **gc);
int						has_empty_quotes_at_start(char *str);
int						is_quote(char c);
char					*remove_outer_quotes(char *str, t_garbage **gc);
int						should_trim_quotes(char *str);
int						has_attached_quotes(char *str);
int						is_matching_quote(char c, char quote_type);
char					*get_clean_word(char *str, t_garbage **gc);
int						is_export_cmd(char *str, t_garbage **gc);
t_tokens				*token_with_pipe(t_tokens *tokens, t_garbage **gc);
bool					is_space(char *input, int i);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dest, char *src, int i, int j,
							t_garbage **gc);
char					*might_replace(t_env *env, char *input, int j,
							char *tmp, t_garbage **gc);
char					*ft_strlcat_mini(char *dst, const char *src,
							size_t dstsize);
void					print_tokens(t_tokens *list);
void					ft_error_export_clean_loop(t_tokens *current, int i,
							char *trimmed, char *clen_trimmed, t_garbage **gc);
void					ft_trim_export(t_tokens *tokens, t_garbage **gc);
void					if_found(char *input, int *i, int *flag, char to_found);
void					process_export_arg(char *arg, t_env *env,
							t_garbage **gc, t_command *cmd);
void					set_env_var(char *arg, t_env *env, t_garbage **gc);
bool					process_redirection(char **parts, int i,
							t_command *cmd_info, t_garbage **gc);
int						write_to_heredoc(int fd, const char *str);
int						init_heredoc(const char *delimiter, char **filename,
							int *fd, t_garbage **gc);
int						process_heredoc_line(int fd, char *line,
							const char *delimiter);
int						finalize_heredoc(int fd, char *filename, int status);
char					*get_temp_filename(t_garbage **gc);
char					*join_env_var(t_env_var *current, t_garbage **gc);
t_env_var				*init_env_var(t_garbage **gc);

int	is_echo_cmd(char *str,t_garbage **gc);
void	ft_clean_words_export(t_tokens *current, t_garbage **gc);


//norminette struct
#endif
