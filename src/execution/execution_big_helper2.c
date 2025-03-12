/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_big_helper2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:20:32 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 14:31:12 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec_context	init_exec_context(t_command *cmd_info, t_garbage **gc,
		int *here_doc_fds)
{
	t_exec_context	ctx;

	ctx.cmd_info = cmd_info;
	ctx.gc = gc;
	ctx.here_doc_fds = here_doc_fds;
	return (ctx);
}

void	handle_other_command(char **parts, t_tokens *tokens,
		t_exec_context *ctx)
{
	t_tokens	*cmd_token;

	if (handle_redirectionnn(parts, ctx->cmd_info, ctx->gc, &ctx->here_doc_fds))
	{
		cmd_token = prepare_cmd_token(parts, tokens, ctx->gc);
		if (cmd_token)
			execute_cmd(cmd_token, parts, ctx->cmd_info, ctx->gc);
	}
}
