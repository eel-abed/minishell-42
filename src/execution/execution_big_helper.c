/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_big_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:06:45 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/09 18:12:20 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	save_restore_fd(int *original_stdout, int *original_stdin, int restore)
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

char	*build_command_string(char **parts, t_garbage **gc)
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

t_tokens	*prepare_cmd_token(char **parts, t_tokens *tokens, t_garbage **gc)
{
	char		*cmd_only;
	t_tokens	*cmd_token;

	cmd_only = build_command_string(parts, gc);
	cmd_token = mini_lstnew(cmd_only, kind_none, gc);
	if (cmd_token)
		cmd_token->env = tokens->env;
	return (cmd_token);
}

void	handle_echo_command(char **parts, t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	if (handle_redirection_tokens(tokens, cmd_info, gc))
		execute_builtin(parts[0], tokens, cmd_info, gc);
}

void	handle_other_command(char **parts, t_tokens *tokens,
		t_command *cmd_info, t_garbage **gc)
{
	t_tokens	*cmd_token;

	if (handle_redirectionnn(parts, cmd_info, gc))
	{
		cmd_token = prepare_cmd_token(parts, tokens, gc);
		if (cmd_token)
			execute_cmd(cmd_token, parts, cmd_info, gc);
	}
}
