/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:50:09 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/06 19:56:58 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	report_error(const char *filename, int error_type)
{
	ft_putstr_fd("minishell: ", 2);
	if (error_type == 0 && filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
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

int	redirect_input(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(strerror(errno), 2);
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
	char		num[32];

	snprintf(num, sizeof(num), "%d", count++);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num, gc);
	if (!filename)
		return (NULL);
	return (filename);
}

int	heredoc(const char *delimiter, t_garbage **gc)
{
	char	*line;
	char	*filename;
	int		fd;
	int		status;
	int		result;

	status = init_heredoc(delimiter, &filename, &fd, gc);
	if (status < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		result = process_heredoc_line(fd, line, delimiter);
		if (result != 0)
		{
			if (result < 0)
				status = -1;
			break ;
		}
	}
	return (finalize_heredoc(fd, filename, status));
}
