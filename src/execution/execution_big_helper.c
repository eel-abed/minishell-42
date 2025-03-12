/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_big_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:06:45 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 12:08:27 by eel-abed         ###   ########.fr       */
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

int	is_redir_operator(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<")
		|| !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

char	*build_command_string(char **parts, t_garbage **gc)
{
	char	*cmd_only;
	char	*temp;
	int		i;

	cmd_only = ft_strdup("", gc);
	i = 0;
	while (parts[i])
	{
		if (is_redir_operator(parts[i]))
		{
			i += 2;
			continue ;
		}
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
		t_garbage **gc, int *here_doc_fds)
{
	char	*first_command;

	first_command = extract_first_cmd(parts);
	if (handle_redirection_tokens(tokens, here_doc_fds, cmd_info, gc))
		execute_builtin(first_command, tokens, cmd_info, gc);
	
}
