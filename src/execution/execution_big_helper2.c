/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_big_helper2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:20:32 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 11:43:16 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_other_command(char **parts, t_tokens *tokens,
		t_command *cmd_info, t_garbage **gc, int **here_doc_fds)
{
	t_tokens	*cmd_token;

	if (handle_redirectionnn(parts, cmd_info, gc, here_doc_fds))
	{
		cmd_token = prepare_cmd_token(parts, tokens, gc);
		if (cmd_token)
			execute_cmd(cmd_token, parts, cmd_info, gc);
	}
}
