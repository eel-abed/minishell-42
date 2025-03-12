/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:15:47 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 15:41:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		handle_sigint(int sig);
void		setup_signals(void);
void		setup_here_doc_signals(void);

void	close_all_std_evetring(void)
{
	int	i;

	i = 3;
	while (i < 2000)
	{
		close(i);
		i++;
	}
}

void	here_doc_sig_handler(int sig)
{
	g_signal_received = sig;
	printf("^C");
	close(STDIN_FILENO);
}

static int	process_heredoc_token(t_tokens *curr, t_heredoc_context *ctx)
{
	int	fd;

	if (curr->type == kind_redir_2left)
	{
		fd = heredoc(curr->next->value, ctx->gc, ctx->original_stdin);
		if (fd == -1)
			return (-1);
		ctx->here_doc_fds[*(ctx->i)] = fd;
		(*(ctx->i))++;
	}
	else if (curr->type == kind_none)
	{
		if (handle_single_token(curr, ctx->here_doc_fds, ctx->gc) == 1)
			return (-1);
	}
	return (0);
}

int	*compute_here_docs(t_tokens *tokens, t_garbage **gc)
{
	t_tokens			*curr;
	int					*here_doc_fds;
	int					i;
	int					original_stdin;
	t_heredoc_context	ctx;

	i = 0;
	curr = tokens;
	original_stdin = dup(STDIN_FILENO);
	here_doc_fds = gc_malloc(gc, (count_here_docs(tokens, gc) * sizeof(int)));
	setup_here_doc_signals();
	ctx.i = &i;
	ctx.here_doc_fds = here_doc_fds;
	ctx.original_stdin = &original_stdin;
	ctx.gc = gc;
	while (curr)
	{
		if (process_heredoc_token(curr, &ctx) == -1)
			return (NULL);
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
	if (!here_doc_fds)
		return (setup_signals());
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
