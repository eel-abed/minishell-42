/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:06:36 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:17 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	finalize_heredoc(int fd, int status)
{
	if (status == 0)
		status = redirect_input(fd);
	return (status);
}

int	redirect_simple_input(const char *filename)
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
	return (0);
}