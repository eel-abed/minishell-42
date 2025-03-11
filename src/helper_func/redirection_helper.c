/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:03:02 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 17:07:08 by mafourni         ###   ########.fr       */
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
	int		i;
	bool	result;

	i = 0;
	while (parts[i])
	{
		result = process_redirection(parts, i, cmd_info, gc, here_doc_fds);
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
	int			status;

	current = tokens;
	while (current)
	{
		if (current->type == kind_redir_right)
		{
			cmd_info->output_file = ft_strdup(current->next->value, gc);
			current->next->value = remove_outer_quotes(current->next->value,
					gc);
			if (redirect_output(current->next->value, 0) < 0)
			{
				cmd_info->exit_status = 1;
				return (false);
			}
		}
		else if (current->type == kind_redir_2right)
		{
			cmd_info->output_file = ft_strdup(current->next->value, gc);
			current->next->value = remove_outer_quotes(current->next->value,
					gc);
			if (redirect_output(current->next->value, 1) < 0)
			{
				cmd_info->exit_status = 1;
				return (false);
			}
		}
		else if (current->type == kind_redir_left)
		{
			cmd_info->input_file = ft_strdup(current->next->value, gc);
			current->next->value = remove_outer_quotes(current->next->value,
					gc);
			if (redirect_simple_input(current->next->value) < 0)
			{
				cmd_info->exit_status = 1;
				return (false);
			}
		}
		else if (current->type == kind_redir_2left)
		{
			cmd_info->delimiter = ft_strdup(current->next->value, gc);
			cmd_info->heredoc_flag = true;
			status = finalize_heredoc(*here_doc_fds, 0);
			here_doc_fds++;
			if (status < 0)
				return (false);
		}
		current = current->next;
	}
	return (true);
}
