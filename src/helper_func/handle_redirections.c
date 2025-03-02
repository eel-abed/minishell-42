/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/02 17:05:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	handle_append_output(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->output_file = ft_strdup(parts[i + 1], gc);
	if (redirect_output(parts[i + 1], 1) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_input_redirection(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->input_file = ft_strdup(parts[i + 1], gc);
	if (redirect_input(parts[i + 1]) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_heredoc(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->delimiter = ft_strdup(parts[i + 1], gc);
	cmd_info->heredoc_flag = true;
	if (heredoc(parts[i + 1], gc) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_output_redirection(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->output_file = ft_strdup(parts[i + 1], gc);
	if (redirect_output(parts[i + 1], 0) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	process_redirection(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!ft_strcmp(parts[i], "<"))
		return (handle_input_redirection(parts, i, cmd_info, gc));
	else if (!ft_strcmp(parts[i], "<<"))
		return (handle_heredoc(parts, i, cmd_info, gc));
	else if (!ft_strcmp(parts[i], ">"))
	{
		if (!handle_output_redirection(parts, i, cmd_info, gc))
			return (false);
		return (false);
	}
	else if (!ft_strcmp(parts[i], ">>"))
	{
		if (!handle_append_output(parts, i, cmd_info, gc))
			return (false);
		return (false);
	}
	return (true);
}
