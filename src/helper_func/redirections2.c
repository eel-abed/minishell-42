/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:03:49 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 15:06:30 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_heredoc_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	unlink(filename);
	return (fd);
}

int	process_heredoc_content(int fd, const char *delimiter, int *original_stdin)
{
	char	*line;
	int		result;

	while (1)
	{
		line = readline(">");
		result = process_heredoc_line(fd, line, delimiter, original_stdin);
		if (result != 0)
		{
			if (result < 0)
				return (-1);
			else
				return (0);
		}
	}
	return (0);
}
