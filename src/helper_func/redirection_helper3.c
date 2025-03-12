/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:42:02 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 14:42:51 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	handle_redir_right(t_tokens *current, t_command *cmd_info,
		t_garbage **gc)
{
	cmd_info->output_file = ft_strdup(current->next->value, gc);
	current->next->value = remove_outer_quotes(current->next->value, gc);
	if (redirect_output(current->next->value, 0) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	handle_redir_2right(t_tokens *current, t_command *cmd_info,
		t_garbage **gc)
{
	cmd_info->output_file = ft_strdup(current->next->value, gc);
	current->next->value = remove_outer_quotes(current->next->value, gc);
	if (redirect_output(current->next->value, 1) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	handle_redir_left(t_tokens *current, t_command *cmd_info,
		t_garbage **gc)
{
	cmd_info->input_file = ft_strdup(current->next->value, gc);
	current->next->value = remove_outer_quotes(current->next->value, gc);
	if (redirect_simple_input(current->next->value) < 0)
	{
		cmd_info->exit_status = 1;
		return (false);
	}
	return (true);
}

bool	handle_redir_2left(t_tokens *current, t_command *cmd_info,
		t_garbage **gc, int **here_doc_fds)
{
	int	status;

	cmd_info->delimiter = ft_strdup(current->next->value, gc);
	cmd_info->heredoc_flag = true;
	status = finalize_heredoc(**here_doc_fds, 0);
	(*here_doc_fds)++;
	return (status >= 0);
}
