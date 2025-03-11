/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 16:10:31 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	handle_append_output(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	int	fd;

	if (!parts[i + 1])
		return (true);
	fd = open(parts[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(parts[i + 1], STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		cmd_info->exit_status = 1;
		return (false);
	}
	close(fd);
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
	char	*clean_filename;
	int		j;

	j = i + 1;
	if (!parts[j])
		return (true);
	clean_filename = remove_outer_quotes(parts[j], gc);
	cmd_info->input_file = ft_strdup(parts[j], gc);
	if (redirect_simple_input(clean_filename) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_heredoc(char **parts, int i, t_command *cmd_info,
		t_garbage **gc, int **here_doc_fds)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->delimiter = ft_strdup(parts[i + 1], gc);
	cmd_info->heredoc_flag = true;
	if (finalize_heredoc(**here_doc_fds, 0) < 0)
	{
		(*here_doc_fds)++;
		cmd_info->exit_status = 1;
		return (false);
	}
	(*here_doc_fds)++;
	return (true);
}

static bool	handle_output_redirection(char **parts, int i, t_command *cmd_info,
		t_garbage **gc)
{
	if (!parts[i + 1])
		return (true);
	cmd_info->output_file = ft_strdup(parts[i + 1], gc);
	cmd_info->output_file = remove_outer_quotes(cmd_info->output_file, gc);
	if (redirect_output(cmd_info->output_file, 0) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	process_redirection(char **parts, int i, t_command *cmd_info,
		t_garbage **gc, int **here_doc_fds)
{
	if (!ft_strcmp(parts[i], "<"))
		return (handle_input_redirection(parts, i, cmd_info, gc));
	else if (!ft_strcmp(parts[i], "<<"))
		return (handle_heredoc(parts, i, cmd_info, gc, here_doc_fds));
	else if (!ft_strcmp(parts[i], ">"))
	{
		return (handle_output_redirection(parts, i, cmd_info, gc));
	}
	else if (!ft_strcmp(parts[i], ">>"))
	{
		return (handle_append_output(parts, i, cmd_info, gc));
	}
	return (true);
}
