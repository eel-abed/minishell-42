/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:03:02 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 15:00:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

bool	handle_redirectionnn(char **parts, t_command *cmd_info, t_garbage **gc,
		int **here_doc_fds)
{
	int				i;
	bool			result;
	t_exec_context	ctx;

	ctx.cmd_info = cmd_info;
	ctx.gc = gc;
	ctx.here_doc_fds = *here_doc_fds;
	i = 0;
	while (parts[i])
	{
		result = process_redirection(parts, i, &ctx);
		if (!result)
			return (i > 0 && (ft_strcmp(parts[i - 1], ">") == 0
					|| ft_strcmp(parts[i - 1], ">>") == 0));
		i++;
	}
	*here_doc_fds = ctx.here_doc_fds;
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
		ft_putstr_fd("minishell: heredoc: write error: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	init_heredoc(char **filename, int *fd, t_garbage **gc)
{
	*filename = get_temp_filename(gc);
	if (!*filename)
	{
		ft_putendl_fd("minishell: heredoc: memory allocation error",
			STDERR_FILENO);
		return (-1);
	}
	*fd = open(*filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
	{
		ft_putstr_fd("minishell: heredoc: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	return (0);
}

bool	handle_redirection_tokens(t_tokens *tokens, int *here_doc_fds,
		t_command *cmd_info, t_garbage **gc)
{
	t_tokens	*current;
	bool		result;

	current = tokens;
	while (current)
	{
		if (current->type == kind_redir_right)
			result = handle_redir_right(current, cmd_info, gc);
		else if (current->type == kind_redir_2right)
			result = handle_redir_2right(current, cmd_info, gc);
		else if (current->type == kind_redir_left)
			result = handle_redir_left(current, cmd_info, gc);
		else if (current->type == kind_redir_2left)
			result = handle_redir_2left(current, cmd_info, gc, &here_doc_fds);
		else
			result = true;
		if (!result)
			return (false);
		current = current->next;
	}
	return (true);
}
