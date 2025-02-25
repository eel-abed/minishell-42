/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 15:05:15 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5))
		return (true);
	return (false);
}

void execute_builtin(char *cmd, t_tokens *tokens, t_command *cmd_info,t_garbage **gc)
{
    if (!ft_strncmp(cmd, "cd", 2))
        cd_builtin(tokens, cmd_info->env, cmd_info,gc);
    else if (!ft_strncmp(cmd, "pwd", 3))
        pwd_builtin();
    else if (!ft_strncmp(cmd, "echo", 4))
        echo_builtin_tokens(tokens,gc);
    else if (!ft_strncmp(cmd, "env", 3))
        env_builtin(cmd_info->env);
    else if (!ft_strncmp(cmd, "exit", 4))
        exit_builtin(tokens, cmd_info,gc);
    else if (!ft_strncmp(cmd, "export", 6))
        export_builtin(tokens, cmd_info->env,gc); 
    else if (!ft_strncmp(cmd, "unset", 5))
        unset_builtin(tokens, cmd_info->env, cmd_info,gc);
}

void execute_command(t_tokens *tokens, t_command *cmd_info,t_garbage **gc)
{
    ft_memset(cmd_info, 0, sizeof(t_command));
    cmd_info->env = tokens->env;
    if (!tokens)
        return;

    char *cmd = tokens->value;

    if (is_builtin(cmd))
        execute_builtin(cmd, tokens, cmd_info,gc);
    else
        cmd_info->exit_status = execute_external_command(tokens, cmd_info,gc);
}
