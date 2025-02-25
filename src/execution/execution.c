/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/24 19:36:36 by eel-abed         ###   ########.fr       */
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
    int original_stdout = dup(STDOUT_FILENO);
    char **parts;
    char *cmd_only;
    
    ft_memset(cmd_info, 0, sizeof(t_command));
    cmd_info->env = tokens->env;
    if (!tokens)
        return;

    // Split the token value into parts
    parts = ft_split(tokens->value, ' ');
    if (!parts)
        return;

    // Handle redirection first
    handle_redirectionnn(parts, cmd_info);

    // Create command string without redirection
    if (cmd_info->output_file)
    {
        size_t cmd_len = ft_strlen(tokens->value) - ft_strlen(" > ") - 
                         ft_strlen(cmd_info->output_file);
        cmd_only = ft_substr(tokens->value, 0, cmd_len);
    }
    else
        cmd_only = ft_strdup(tokens->value);

    // Create new token with command only
    t_tokens *cmd_token = mini_lstnew(cmd_only, kind_none);
    if (cmd_token)
    {
        cmd_token->env = tokens->env;
        if (is_builtin(parts[0]))
            execute_builtin(parts[0], cmd_token, cmd_info);
        else
            cmd_info->exit_status = execute_external_command(cmd_token, cmd_info);
        free(cmd_token);
    }

    // Cleanup
    if (cmd_only)
        free(cmd_only);
    if (cmd_info->output_file)
        free(cmd_info->output_file);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
    free_paths(parts);
}
