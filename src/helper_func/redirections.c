/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:50:09 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 15:04:51 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	report_error(const char *filename, int error_type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_type == 0 && filename)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int	redirect_output(const char *filename, int append_mode)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append_mode)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		report_error(filename, 0);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		report_error(NULL, 1);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

char	*get_temp_filename(t_garbage **gc)
{
	static int	count = 0;
	char		*filename;
	char		*filename_count;

	filename_count = ft_itoa(count++, gc);
	filename = ft_strjoin("/tmp/minishell_heredoc_", filename_count, gc);
	if (!filename)
		return (NULL);
	return (filename);
}

int	heredoc(const char *delimiter, t_garbage **gc, int *original_stdin)
{
	char	*filename;
	int		fd;
	int		status;

	status = init_heredoc(&filename, &fd, gc);
	if (status < 0)
		return (-1);
	status = process_heredoc_content(fd, delimiter, original_stdin);
	if (status < 0 || g_signal_received == SIGINT)
		return (-1);
	return (open_heredoc_file(filename));
}
