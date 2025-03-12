/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainfini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:09:45 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 16:11:55 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	initialize_shell(t_env **env, t_command *cmd, char **envp,
		t_garbage **gc)
{
	*env = init_env(envp, gc);
	if (!*env)
		exit(1);
	setup_signals();
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->env = *env;
	cmd->exit_status = 0;
}

void	process_input(char *input, t_tokens **token_clean, t_command *cmd,
		t_garbage **gc)
{
	if (g_signal_received == SIGINT)
	{
		cmd->exit_status = 130;
		g_signal_received = 0;
	}
	if (strlen(input) > 0)
	{
		*token_clean = ft_lexer(input, cmd->env, gc, cmd);
		if (*token_clean)
			handle_command_line(*token_clean, cmd, gc);
	}
}

void	cleanup_shell(t_garbage **gc)
{
	gc_free_all(gc);
	printf("exit\n");
	close_all_std_evetring();
	close(3);
	close(2);
	close(1);
	close(0);
}
