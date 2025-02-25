/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:50:09 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 16:12:02 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

// static char	*get_temp_filename(void)
// {
// 	static int	count = 0;
// 	char		*filename;
// 	char		num[32];

// 	snprintf(num, sizeof(num), "%d", count++);
// 	filename = ft_strjoin("/tmp/minishell_heredoc_", num);
// 	if (!filename)
// 		return (NULL);
// 	return (filename);
// }

// static int	write_to_heredoc(int fd, const char *str)
// {
// 	ssize_t	len;
// 	ssize_t	written;

// 	len = strlen(str);
// 	written = write(fd, str, len);
// 	if (written != len)
// 	{
// 		ft_putstr_fd("minishell: heredoc: write error: ", 2);
// 		ft_putendl_fd(strerror(errno), 2);
// 		return (-1);
// 	}
// 	return (0);
// }

// int	heredoc(const char *delimiter)
// {
// 	char	*line;
// 	char	*filename;
// 	int		fd;
// 	int		status;

// 	status = 0;
// 	if (!delimiter || !*delimiter)
// 	{
// 		ft_putendl_fd("minishell: heredoc: delimiter cannot be empty", 2);
// 		return (-1);
// 	}
// 	filename = get_temp_filename();
// 	if (!filename)
// 	{
// 		ft_putendl_fd("minishell: heredoc: memory allocation error", 2);
// 		return (-1);
// 	}
// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("minishell: heredoc: ", 2);
// 		ft_putendl_fd(strerror(errno), 2);
// 		free(filename);
// 		return (-1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file",
// 				2);
// 			break ;
// 		}
// 		if (strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		if (write_to_heredoc(fd, line) < 0 || write_to_heredoc(fd, "\n") < 0)
// 		{
// 			status = -1;
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// 	close(fd);
// 	if (status == 0)
// 	{
// 		status = redirect_input(filename);
// 		if (status < 0)
// 		{
// 			ft_putstr_fd("minishell: heredoc: failed to redirect input: ", 2);
// 			ft_putendl_fd(strerror(errno), 2);
// 		}
// 	}
// 	unlink(filename);
// 	free(filename);
// 	return (status);
// }
