/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/20 19:12:12 by eel-abed         ###   ########.fr       */
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

void	execute_builtin(char *cmd, char **args, t_command *cmd_info)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(args, cmd_info->env, cmd_info);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin(args);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin(cmd_info->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(args, cmd_info);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(args, cmd_info->env);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(args, cmd_info->env, cmd_info);
}

void execute_command(t_tokens *tokens, t_command *cmd_info)
{
	// Reset command info
	ft_memset(cmd_info, 0, sizeof(t_command));

	// Check if tokens are empty
	if (!tokens)
		return;

	// The first token's value is the command
	char *cmd = tokens->value;

	// Check if first token is a builtin
	if (is_builtin(cmd))
	{
		// Prepare arguments for builtin
		char **builtin_args = malloc(sizeof(char *) * (mini_lstsize(tokens) + 1));
		t_tokens *current = tokens;
		int i = 0;

		while (current)
		{
			builtin_args[i] = current->value;
			current = current->next;
			i++;
		}
		builtin_args[i] = NULL;

		execute_builtin(cmd, builtin_args, cmd_info);
		free(builtin_args);
	}
	else
	{
		// Execute external command directly with tokens
		// cmd_info->exit_status = execute_external_command(tokens, cmd_info);
	}
}
