/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	handle_append_output(char **parts, int i, t_exec_context *ctx)
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
		ctx->cmd_info->exit_status = 1;
		return (false);
	}
	close(fd);
	ctx->cmd_info->output_file = ft_strdup(parts[i + 1], ctx->gc);
	if (redirect_output(parts[i + 1], 1) < 0)
	{
		ctx->cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_input_redirection(char **parts, int i, t_exec_context *ctx)
{
	char	*clean_filename;
	int		j;

	j = i + 1;
	if (!parts[j])
		return (true);
	clean_filename = remove_outer_quotes(parts[j], ctx->gc);
	ctx->cmd_info->input_file = ft_strdup(parts[j], ctx->gc);
	if (redirect_simple_input(clean_filename) < 0)
	{
		ctx->cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

static bool	handle_heredoc(char **parts, int i, t_exec_context *ctx)
{
	if (!parts[i + 1])
		return (true);
	ctx->cmd_info->delimiter = ft_strdup(parts[i + 1], ctx->gc);
	ctx->cmd_info->heredoc_flag = true;
	if (finalize_heredoc(*ctx->here_doc_fds, 0) < 0)
	{
		ctx->here_doc_fds++;
		ctx->cmd_info->exit_status = 1;
		return (false);
	}
	ctx->here_doc_fds++;
	return (true);
}

static bool	handle_output_redirection(char **parts, int i, t_exec_context *ctx)
{
	if (!parts[i + 1])
		return (true);
	ctx->cmd_info->output_file = ft_strdup(parts[i + 1], ctx->gc);
	ctx->cmd_info->output_file = remove_outer_quotes(ctx->cmd_info->output_file,
			ctx->gc);
	if (redirect_output(ctx->cmd_info->output_file, 0) < 0)
	{
		ctx->cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	process_redirection(char **parts, int i, t_exec_context *ctx)
{
	if (!ft_strcmp(parts[i], "<"))
		return (handle_input_redirection(parts, i, ctx));
	else if (!ft_strcmp(parts[i], "<<"))
		return (handle_heredoc(parts, i, ctx));
	else if (!ft_strcmp(parts[i], ">"))
		return (handle_output_redirection(parts, i, ctx));
	else if (!ft_strcmp(parts[i], ">>"))
		return (handle_append_output(parts, i, ctx));
	return (true);
}
