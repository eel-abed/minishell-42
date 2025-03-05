/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/05 17:02:41 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	save_restore_fd(int *original_stdout, int *original_stdin,
		int restore)
{
	if (restore)
	{
		dup2(*original_stdout, STDOUT_FILENO);
		dup2(*original_stdin, STDIN_FILENO);
		close(*original_stdout);
		close(*original_stdin);
	}
	else
	{
		*original_stdout = dup(STDOUT_FILENO);
		*original_stdin = dup(STDIN_FILENO);
	}
}

static char	*build_command_string(char **parts, t_garbage **gc)
{
	char	*cmd_only;
	char	*temp;
	int		i;

	cmd_only = NULL;
	i = 0;
	while (parts[i] && ft_strcmp(parts[i], ">") != 0 && ft_strcmp(parts[i],
			">>") != 0 && ft_strcmp(parts[i], "<") != 0 && ft_strcmp(parts[i],
			"<<") != 0)
	{
		if (cmd_only == NULL)
			cmd_only = ft_strdup(parts[i], gc);
		else
		{
			temp = cmd_only;
			cmd_only = ft_strjoin(temp, " ", gc);
			cmd_only = ft_strjoin(cmd_only, parts[i], gc);
		}
		i++;
	}
	if (!cmd_only)
		cmd_only = ft_strdup("", gc);
	return (cmd_only);
}

static t_tokens	*prepare_cmd_token(char **parts, t_tokens *tokens,
		t_garbage **gc)
{
	char		*cmd_only;
	t_tokens	*cmd_token;

	cmd_only = build_command_string(parts, gc);
	cmd_token = mini_lstnew(cmd_only, kind_none, gc);
	if (cmd_token)
		cmd_token->env = tokens->env;
	return (cmd_token);
}

static void	execute_cmd(t_tokens *cmd_token, char **parts, t_command *cmd_info,
		t_garbage **gc)
{
	if (is_builtin(parts[0]))
		execute_builtin(parts[0], cmd_token, cmd_info, gc);
	else
		cmd_info->exit_status = execute_external_command(cmd_token, cmd_info,
				gc);
}

void	execute_command(t_tokens *tokens, t_command *cmd_info, t_garbage **gc)
{
	int			original_stdout;
	int			original_stdin;
	char		**parts;
	t_tokens	*cmd_token;

	save_restore_fd(&original_stdout, &original_stdin, 0);
	ft_memset(cmd_info, 0, sizeof(t_command));
	cmd_info->env = tokens->env;
	if (!tokens)
		return ;
	parts = ft_split(tokens->value, ' ', gc);
	if (!parts)
	{
		save_restore_fd(&original_stdout, &original_stdin, 1);
		return ;
	}
	if (parts[0] && !ft_strcmp(parts[0], "echo"))
	{
		// Handle redirections for echo with tokens directly
		if (!handle_redirection_tokens(tokens, cmd_info, gc))
		{
			save_restore_fd(&original_stdout, &original_stdin, 1);
			return ;
		}
		execute_builtin(parts[0], tokens, cmd_info, gc);
	}
	else
	{
		if (!handle_redirectionnn(parts, cmd_info, gc))
		{
			save_restore_fd(&original_stdout, &original_stdin, 1);
			return ;
		}
		cmd_token = prepare_cmd_token(parts, tokens, gc);
		if (cmd_token)
			execute_cmd(cmd_token, parts, cmd_info, gc);
	}
	save_restore_fd(&original_stdout, &original_stdin, 1);
}
