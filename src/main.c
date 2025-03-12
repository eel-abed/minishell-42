/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2025/03/12 20:10:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			g_signal_received = 0;

int	contains_here_doc(char *token_value, t_operator_kind token_type,
		t_garbage **gc)
{
	char	**token_split;
	int		i;
	int		j;

	if (token_type == kind_none && ft_strchr(token_value, '<'))
	{
		return (0);
	}
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
		if (tmp->type == kind_redir_2left)
			i++;
		else if (tmp->type == kind_none && contains_here_doc(tmp->value,
				tmp->type, gc))
			i += contains_here_doc(tmp->value, tmp->type, gc);
		tmp = tmp->next;
	}
	return (i);
}

static int	process_heredoc_token(char **split_token, int j, int *i,
		t_heredoc_data *data)
{
	int	fd;

	if (!ft_strcmp(split_token[j], "<<"))
		return (j + 1);
	else if (ft_strcmp(split_token[j], "<<") && ft_strcmp(split_token[j - 1],
			"<<"))
		return (-1);
	fd = heredoc(split_token[j], data->gc, data->original_stdin);
	if (fd == -1)
		return (-2);
	data->here_doc_fds[*i] = fd;
	(*i)++;
	return (j + 1);
}

int	handle_single_token(t_tokens *token, int *here_doc_fds, t_garbage **gc)
{
	int				j;
	int				i;
	char			**split_token;
	int				original_stdin;
	t_heredoc_data	data;

	if (token->type == kind_none && ft_strchr(token->value, '<'))
		return (0);
	j = 1;
	i = 0;
	original_stdin = dup(STDIN_FILENO);
	split_token = ft_split(token->value, ' ', gc);
	data.here_doc_fds = here_doc_fds;
	data.gc = gc;
	data.original_stdin = &original_stdin;
	while (split_token[j])
	{
		j = process_heredoc_token(split_token, j, &i, &data);
		if (j == -1)
			break ;
		if (j == -2)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env		*env;
	t_command	cmd;
	t_garbage	*gc;

	gc = NULL;
	(void)argc;
	(void)argv;
	init_shell(&cmd, &env, envp, &gc);
	if (!env)
		return (1);
	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		process_input(input, &cmd, &gc);
		free(input);
	}
	cleanup_shell(&gc);
	return (0);
}
