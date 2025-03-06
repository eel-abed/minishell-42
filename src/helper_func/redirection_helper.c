/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:03:02 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/06 19:56:16 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	handle_redirectionnn(char **parts, t_command *cmd_info, t_garbage **gc)
{
	int		i;
	bool	result;

	i = 0;
	while (parts[i])
	{
		result = process_redirection(parts, i, cmd_info, gc);
		if (!result)
			return (i > 0 && (ft_strcmp(parts[i - 1], ">") == 0
					|| ft_strcmp(parts[i - 1], ">>") == 0));
		i++;
	}
	return (true);
}

int	write_to_heredoc(int fd, const char *str)
{
	ssize_t	len;
	ssize_t	written;

	len = ft_strlen(str);
	written = write(fd, str, len);
	if (written != len)
	{
		ft_putstr_fd("minishell: heredoc: write error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	return (0);
}

int	init_heredoc(const char *delimiter, char **filename, int *fd,
		t_garbage **gc)
{
	if (!delimiter || !*delimiter)
	{
		ft_putendl_fd("minishell: heredoc: delimiter cannot be empty", 2);
		return (-1);
	}
	*filename = get_temp_filename(gc);
	if (!*filename)
	{
		ft_putendl_fd("minishell: heredoc: memory allocation error", 2);
		return (-1);
	}
	*fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
	{
		ft_putstr_fd("minishell: heredoc: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	return (0);
}

int	process_heredoc_line(int fd, char *line, const char *delimiter)
{
	if (!line)
	{
		ft_putendl_fd("minishell: warning: here-document delimited by EOF", 2);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	if (write_to_heredoc(fd, line) < 0 || write_to_heredoc(fd, "\n") < 0)
	{
		free(line);
		return (-1);
	}
	free(line);
	return (0);
}

int	finalize_heredoc(int fd, char *filename, int status)
{
	close(fd);
	if (status == 0)
		status = redirect_input(filename);
	if (status < 0)
		ft_putstr_fd("minishell: heredoc: failed to redirect input: ", 2);
	unlink(filename);
	return (status);
}
bool	handle_redirection_tokens(t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	t_tokens	*current;
	bool		found_redirection;

	current = tokens;
	found_redirection = false;
	while (current)
	{
		if (current->type == kind_redir_right)
		{
			found_redirection = true;
			if (current->next)
			{
				cmd_info->output_file = ft_strdup(current->next->value, gc);
				if (redirect_output(current->next->value, 0) < 0)
				{
					cmd_info->exit_status = 1;
					return (false);
				}
			}
		}
		else if (current->type == kind_redir_2right)
		{
			found_redirection = true;
			if (current->next)
			{
				cmd_info->output_file = ft_strdup(current->next->value, gc);
				if (redirect_output(current->next->value, 1) < 0)
				{
					cmd_info->exit_status = 1;
					return (false);
				}
			}
		}
		else if (current->type == kind_redir_left)
		{
			found_redirection = true;
			if (current->next)
			{
				cmd_info->input_file = ft_strdup(current->next->value, gc);
				if (redirect_input(current->next->value) < 0)
				{
					cmd_info->exit_status = 1;
					return (false);
				}
			}
		}
		else if (current->type == kind_redir_2left)
		{
			found_redirection = true;
			if (current->next)
			{
				cmd_info->delimiter = ft_strdup(current->next->value, gc);
				cmd_info->heredoc_flag = true;
				if (heredoc(current->next->value, gc) < 0)
				{
					cmd_info->exit_status = 1;
					return (false);
				}
			}
		}
		current = current->next;
	}
	return (true);
}
