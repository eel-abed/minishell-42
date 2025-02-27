/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/26 19:26:22 by eel-abed         ###   ########.fr       */
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

void	execute_builtin(char *cmd, t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(tokens, cmd_info->env, cmd_info, gc);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin_tokens(tokens, gc);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin(cmd_info->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(tokens, cmd_info, gc);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(tokens, cmd_info->env, gc);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(tokens, cmd_info->env, cmd_info, gc);
}

void	execute_command(t_tokens *tokens, t_command *cmd_info, t_garbage **gc)
{
	int			original_stdout;
	int			original_stdin;
	char		**parts;
	char		*cmd_only;
	t_tokens	*cmd_token;

	original_stdout = dup(STDOUT_FILENO);
	original_stdin = dup(STDIN_FILENO);
	ft_memset(cmd_info, 0, sizeof(t_command));
	cmd_info->env = tokens->env;
	if (!tokens)
		return ;
	// Split the token value into parts
	parts = ft_split(tokens->value, ' ', gc);
	if (!parts)
		return ;
	// Handle redirection first
	if (!handle_redirectionnn(parts, cmd_info, gc))
	{
		// If redirection failed, cleanup and return without executing the command
		dup2(original_stdout, STDOUT_FILENO);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdout);
		close(original_stdin);
		return;
	}
	
	// Create command string without redirection
	cmd_only = NULL;
	int i = 0;
	while (parts[i] && 
	       ft_strcmp(parts[i], ">") != 0 && 
	       ft_strcmp(parts[i], ">>") != 0 && 
	       ft_strcmp(parts[i], "<") != 0 && 
	       ft_strcmp(parts[i], "<<") != 0)
	{
	    if (cmd_only == NULL)
	    {
	        cmd_only = ft_strdup(parts[i], gc);
	    }
	    else
	    {
	        char *temp = cmd_only;
	        cmd_only = ft_strjoin(temp, " ", gc);
	        cmd_only = ft_strjoin(cmd_only, parts[i], gc);
	    }
	    i++;
	}

	if (!cmd_only)
	    cmd_only = ft_strdup("", gc);
	
	cmd_token = mini_lstnew(cmd_only, kind_none, gc);
	if (cmd_token)
	{
		cmd_token->env = tokens->env;
		if (is_builtin(parts[0]))
			execute_builtin(parts[0], cmd_token, cmd_info, gc);
		else
			cmd_info->exit_status = execute_external_command(cmd_token,
					cmd_info, gc);
	}
	dup2(original_stdout, STDOUT_FILENO);
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdout);
	close(original_stdin);
}
