/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2025/03/09 17:12:19 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_signal_received = 0;

int contains_here_doc(char *token_value, t_garbage **gc)
{
	char **token_split;
	int i;
	int j;

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

int count_here_docs(t_tokens *tokens, t_garbage **gc)
{
	int i;
	t_tokens *tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == kind_redir_2left || (tmp->type == kind_none && contains_here_doc(tmp->value, gc)))
			i += contains_here_doc(tmp->value, gc);
		tmp = tmp->next;
	}
	return (i);
}

void *handle_single_token(t_tokens *token, int *here_doc_fds, t_garbage **gc)
{
	int j;
	int i;
	char **split_token;
	int fd;

	j = 1;
	i = 0;
	split_token = ft_split(token->value, ' ', gc);
	while (split_token[j])
	{
		if (!ft_strcmp(split_token[j], "<<"))
		{
			j++;
			continue;
		}
		else if (ft_strcmp(split_token[j], "<<") && ft_strcmp(split_token[j - 1], "<<"))
			break;
		fd = heredoc(split_token[j], gc);
		if (fd == -1)
			return (NULL);
		here_doc_fds[i] = fd;
		i++;
		j++;
	}
	return (NULL);
}

void print_int_tab(int *tab)
{
	int i;

	i = 0;
	while (i < 3)
	{
		printf("tab[%d] -> %d\n", i, tab[i]);
		i++;
	}
}

int *compute_here_docs(t_tokens *tokens, t_garbage **gc) // ! OK
{
	t_tokens *curr;
	int fd;
	int *here_doc_fds;
	int i;

	curr = tokens;
	i = 0;
	here_doc_fds = gc_malloc(gc, (count_here_docs(tokens, gc) * sizeof (int)));
	while (curr)
	{
		if (curr->type == kind_redir_2left )
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
	int *here_doc_fds;

	here_doc_fds = compute_here_docs(tokens,  gc);
	current = tokens;
	while (current)
	{
		if (current->type == kind_pipe)
		{
			execute_piped_commands(tokens, cmd_info, gc, &here_doc_fds);
			// gc_free_all(gc);
			return ;
		}
		current = current->next;
	}
	execute_command(tokens, cmd_info, gc, &here_doc_fds);
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
	env = init_env(envp, &gc);
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
			break ;
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
	return (0);
}
