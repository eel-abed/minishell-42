/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:37 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/22 17:26:16 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../libft/libft.h"

extern char **environ;

typedef struct s_command
{
    char	*input_file;
    char	*output_file;
    char	*delimiter;
    bool	heredoc_flag;
    char	**cmd1;
    char	**cmd2;
    int		pipefd[2];
    pid_t	pid1;
    pid_t	pid2;
}	t_command;

bool is_builtin(char *cmd);
void execute_builtin(char *cmd, char **args);
void cd_builtin(char **args);
void pwd_builtin(void);
void echo_builtin(char **args);
void env_builtin(void);
void exit_builtin(char **args);
void export_builtin(char **args);
void unset_builtin(char **args);
void	execute_command(char **args);
int execute_external_command(char **args);
int redirect_input(const char *file);
int redirect_output(const char *file);
int redirect_append(const char *file);
int heredoc(const char *delimiter);
pid_t   fork_and_execute_first(t_command *cmd_info);
pid_t   fork_and_execute_second(t_command *cmd_info);
int	handle_input_redirect(char **args, int i, t_command *cmd_info);
int	handle_output_redirect(char **args, int i, t_command *cmd_info);
int	handle_append_redirect(char **args, int i, t_command *cmd_info);
int	handle_heredoc(char **args, int i, t_command *cmd_info);



#endif
