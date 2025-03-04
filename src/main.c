/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2025/03/04 19:46:21 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_received = 0;

void handle_command_line(t_tokens *tokens, t_command *cmd_info, t_garbage **gc)
{
    t_tokens *current = tokens;

    while (current)
    {
        if (current->type == kind_pipe)
        {
            execute_piped_commands(tokens, cmd_info, gc);
            return;
        }
        current = current->next;
    }
    execute_command(tokens, cmd_info, gc);
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*token_clean;
	char		*input;
	t_env		*env;
	t_command	cmd;
	t_garbage	*gc;

	gc = NULL;
	(void)argc;
	(void)argv;
	env = init_env(envp,&gc);
	if (!env)
		return (1);
	setup_signals();
	ft_memset(&cmd, 0, sizeof(t_command));
	cmd.env = env;
	cmd.exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break;
		if (strlen(input) > 0)
		{
			add_history(input);
			token_clean = ft_lexer(input, env,&gc,&cmd);
			if (token_clean)
				handle_command_line(token_clean, &cmd,&gc);
		}
		if(input)
			free(input);
	}
	gc_free_all(&gc);
	return (0);
}

