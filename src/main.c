/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2025/03/11 16:22:18 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_signal_received = 0;

int	contains_here_doc(char *token_value, t_garbage **gc)
{
	char	**token_split;
	int		i;
	int		j;

	token_split = ft_split(token_value, ' ', gc);
	i = 0;
	j = 0;
	while (token_split[i])
	{
		if (!ft_strcmp(token_split[i], "<<"))
			j++;
		i++;
	}
	return (j);
}

int	count_here_docs(t_tokens *tokens, t_garbage **gc)
{
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == kind_redir_2left || (tmp->type == kind_none
				&& contains_here_doc(tmp->value, gc)))
			i += contains_here_doc(tmp->value, gc);
		tmp = tmp->next;
	}
	return (i);
}

int	handle_single_token(t_tokens *token, int *here_doc_fds, t_garbage **gc)
{
	int		j;
	int		i;
	char	**split_token;
	int		fd;
	int original_stdin;

	j = 1;
	i = 0;
	original_stdin = dup(STDIN_FILENO);
	split_token = ft_split(token->value, ' ', gc);
	while (split_token[j])
	{
		if (!ft_strcmp(split_token[j], "<<"))
		{
			j++;
			continue ;
		}
		else if (ft_strcmp(split_token[j], "<<") && ft_strcmp(split_token[j
				- 1], "<<"))
			break ;
		fd = heredoc(split_token[j], gc, &original_stdin);
		if (fd == -1)
			return (1);
		here_doc_fds[i] = fd;
		i++;
		j++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*token_clean;
	char		*input;
	t_env		*env;
	t_command	cmd;
	t_garbage	*gc;

	gc = NULL;
	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	env = init_env(envp, &gc);
	if (!env)
		return (1);
	setup_signals();
	ft_memset(&cmd, 0, sizeof(t_command));
	cmd.env = env;
	cmd.exit_status = 0;
	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			// Mettre a jour le exit status
		}
		if (strlen(input) > 0)
		{
			token_clean = ft_lexer(input, env, &gc, &cmd);
			if (token_clean)
				handle_command_line(token_clean, &cmd, &gc);
		}
		if (input)
			free(input);
	}
	gc_free_all(&gc);
	printf("exit\n");
	close_all_std_evetring();
	close(3);
	close(2);
	close(1);
	close(0);
	return (0);
}
