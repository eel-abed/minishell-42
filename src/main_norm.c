/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:47 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/11 16:16:25 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_all_std_evetring(void)
{
	int i = 3;
	while (i < 2000)
	{
		close(i);
		i++;
	}
}
int	*compute_here_docs(t_tokens *tokens, t_garbage **gc) // ! OK
{
	t_tokens *curr;

	int fd;
	int *here_doc_fds;
	int i;

	curr = tokens;
	i = 0;
	here_doc_fds = gc_malloc(gc, (count_here_docs(tokens, gc) * sizeof(int)));
	while (curr)
	{
		if (curr->type == kind_redir_2left)
		{
			fd = heredoc(curr->next->value, gc);
			if (fd == -1)
				return (NULL);
			here_doc_fds[i] = fd;
			i++;
		}
		else if (curr->type == kind_none)
			handle_single_token(curr, here_doc_fds, gc);
		curr = curr->next;
	}
	return (here_doc_fds);
}

void	handle_command_line(t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	t_tokens	*current;
	int			*here_doc_fds;

	g_signal_received = -1;
	here_doc_fds = compute_here_docs(tokens, gc);
	current = tokens;
	while (current)
	{
		if (current->type == kind_pipe)
		{
			execute_piped_commands(tokens, cmd_info, gc, &here_doc_fds);
			g_signal_received = 0;
			return ;
		}
		current = current->next;
	}
	execute_command(tokens, cmd_info, gc, &here_doc_fds);
	g_signal_received = 0;
}