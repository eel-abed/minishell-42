/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainhelperla.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:04:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 17:06:06 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell(t_command *cmd, t_env **env, char **envp, t_garbage **gc)
{
	rl_catch_signals = 0;
	*env = init_env(envp, gc);
	setup_signals();
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->env = *env;
	cmd->exit_status = 0;
}

void	process_input(char *input, t_command *cmd, t_garbage **gc)
{
	t_tokens	*token_clean;

	if (g_signal_received == SIGINT)
	{
		cmd->exit_status = 130;
		g_signal_received = 0;
	}
	if (strlen(input) > 0)
	{
		token_clean = ft_lexer(input, cmd->env, gc, cmd);
		if (token_clean)
			handle_command_line(token_clean, cmd, gc);
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
