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

void	handle_sigint(int sig);
void	setup_signals(void);
void	setup_here_doc_signals(void);

void	close_all_std_evetring(void)
{
	int i = 3;
	while (i < 2000)
	{
		close(i);
		i++;
	}
}

void here_doc_sig_handler(int sig)
{
	g_signal_received = sig;
	close(STDIN_FILENO);
	printf("\n");
}

int	*compute_here_docs(t_tokens *tokens, t_garbage **gc) // ! OK
{
	t_tokens *curr;

	int fd;
	int *here_doc_fds;
	int i;
	int original_stdin;

	curr = tokens;
	i = 0;
	original_stdin = dup(STDIN_FILENO);
	here_doc_fds = gc_malloc(gc, (count_here_docs(tokens, gc) * sizeof(int)));
	setup_here_doc_signals();
	while (curr)
	{
		if (curr->type == kind_redir_2left)
		{
			fd = heredoc(curr->next->value, gc, &original_stdin);
			if (fd == -1)
				return (NULL);
			here_doc_fds[i] = fd;
			i++;
		}
		else if (curr->type == kind_none)
		{
			if (handle_single_token(curr, here_doc_fds, gc) == 1)
				return (setup_signals() , NULL);
		}
		curr = curr->next;
	}
	setup_signals();
	return (here_doc_fds);
}

void	handle_command_line(t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	t_tokens	*current;
	int			*here_doc_fds;

	g_signal_received = -1;
	here_doc_fds = compute_here_docs(tokens, gc);
	if (!here_doc_fds)
		return ;
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
