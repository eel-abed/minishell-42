/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 14:31:33 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	setup_command(t_tokens *tokens, t_command *cmd_info, char ***parts,
		t_garbage **gc)
{
	ft_memset(cmd_info, 0, sizeof(t_command));
	cmd_info->env = tokens->env;
	if (!tokens)
		return (0);
	if (is_cat_cmd(tokens->value, gc) == 0)
		*parts = ft_split_hors_quotes(tokens->value, ' ', gc);
	else
		*parts = ft_split(tokens->value, ' ', gc);
	return (*parts != NULL);
}

char	*rebuild_command(t_tokens *tokens, t_garbage **gc)
{
	t_tokens	*tmp;
	char		*cmd;

	tmp = tokens;
	cmd = ft_strdup("", gc);
	while (tmp && is_redir_operator(tmp->value))
	{
		tmp = tmp->next->next;
	}
	while (tmp && !is_redir_operator(tmp->value))
	{
		cmd = ft_strjoin(cmd, tmp->value, gc);
		tmp = tmp->next;
	}
	return (cmd);
}

void	execute_command(t_tokens *tokens, t_command *cmd_info, t_garbage **gc,
		int **here_doc_fds)
{
	int				original_stdout;
	int				original_stdin;
	char			**parts;
	t_exec_context	ctx;

	save_restore_fd(&original_stdout, &original_stdin, 0);
	if (!setup_command(tokens, cmd_info, &parts, gc))
	{
		save_restore_fd(&original_stdout, &original_stdin, 1);
		return ;
	}
	if (parts[0] && contain_echo_token(tokens))
	{
		parts = ft_split(rebuild_command(tokens, gc), ' ', gc);
		ctx = init_exec_context(cmd_info, gc, *here_doc_fds);
		handle_echo_command(parts, tokens, &ctx);
	}
	else
	{
		ctx = init_exec_context(cmd_info, gc, *here_doc_fds);
		handle_other_command(parts, tokens, &ctx);
	}
	save_restore_fd(&original_stdout, &original_stdin, 1);
	close_all_std_evetring();
}

static int	init_split(char const *s, char c, char ***result, t_garbage **gc)
{
	int	word_count;

	if (!s)
		return (0);
	word_count = count_words_with_quotes(s, c);
	*result = gc_malloc(gc, sizeof(char *) * (word_count + 1));
	if (!*result)
		return (0);
	return (word_count);
}

char	**ft_split_hors_quotes(char const *s, char c, t_garbage **gc)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;

	word_count = init_split(s, c, &result, gc);
	if (!word_count && !s)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			result[j] = extract_word(s, &i, c, gc);
			if (!result[j])
				return (NULL);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
