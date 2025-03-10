/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:36:47 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/05 17:36:03 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(char *cmd, t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(tokens, cmd_info->env, cmd_info, gc);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin_tokens(tokens);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin(cmd_info->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(tokens, cmd_info, gc);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(tokens, cmd_info->env, gc, cmd_info);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(tokens, cmd_info->env, cmd_info, gc);
}

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
