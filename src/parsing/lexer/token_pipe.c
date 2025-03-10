/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:43 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 19:29:26 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*build_cmd_str(t_tokens *cmd_start, t_tokens *current, t_tokens *tokens,
		t_garbage **gc)
{
	char	*cmd_str;
	char	*tmp;

	cmd_str = ft_strdup("", gc);
	while (cmd_start != current)
	{
		if (cmd_start != tokens)
		{
			tmp = cmd_str;
			cmd_str = ft_strjoin(cmd_str, " ", gc);
		}
		tmp = cmd_str;
		cmd_str = ft_strjoin(cmd_str, cmd_start->value, gc);
		cmd_start = cmd_start->next;
	}
	return (cmd_str);
}

char	*handle_last_token(t_wpipe_norm wpipe, t_tokens *current,
		t_tokens *tokens, t_garbage **gc)
{
	char	*tmp;

	if (!current->next && current->type != kind_pipe)
	{
		if (wpipe.cmd_start != tokens || ft_strlen(wpipe.cmd_str) > 0)
		{
			tmp = wpipe.cmd_str;
			wpipe.cmd_str = ft_strjoin(wpipe.cmd_str, " ", gc);
		}
		tmp = wpipe.cmd_str;
		wpipe.cmd_str = ft_strjoin(wpipe.cmd_str, current->value, gc);
	}
	return (wpipe.cmd_str);
}

void	add_pipe_token(t_tokens **result, t_tokens **cmd_start,
		t_tokens *current, t_garbage **gc)
{
	t_tokens	*new_token;

	if (current->type == kind_pipe)
	{
		new_token = mini_lstnew(ft_strdup("|", gc), kind_pipe, gc);
		mini_lstadd_back(result, new_token);
		*cmd_start = current->next;
	}
}

t_tokens	*token_with_pipe(t_tokens *tokens, t_garbage **gc)
{
	t_tokens		*current;
	t_wpipe_norm	wpipe;
	int				isecho;

	if (!tokens)
		return (NULL);
	wpipe.result = NULL;
	wpipe.cmd_str = NULL;
	wpipe.new_token = NULL;
	current = tokens;
	wpipe.cmd_start = tokens;
	isecho = 0;
	while (current)
	{
		if (is_echo_cmd(current->value, gc) == 1)
			isecho = 1;
		if (current->type == kind_pipe || (!current->next && isecho == 0))
		{
			if (isecho == 0)
			{
				wpipe.cmd_str = build_cmd_str(wpipe.cmd_start, current, tokens,
						gc);
				wpipe.cmd_str = handle_last_token(wpipe, current, tokens, gc);
				wpipe.new_token = mini_lstnew(wpipe.cmd_str, kind_none, gc);
				mini_lstadd_back(&wpipe.result, wpipe.new_token);
				add_pipe_token(&wpipe.result, &wpipe.cmd_start, current, gc);
				wpipe.cmd_start = current->next;
			}
			else
			{
				add_pipe_token(&wpipe.result, &wpipe.cmd_start, current, gc);
				wpipe.cmd_start = current->next;
			}
			isecho = 0;
		}
		else if (isecho == 1)
		{
			wpipe.new_token = mini_lstnew(ft_strdup(current->value, gc),
					current->type, gc);
			mini_lstadd_back(&wpipe.result, wpipe.new_token);
			add_pipe_token(&wpipe.result, &wpipe.cmd_start, current, gc);
			wpipe.cmd_start = current->next;
		}
		current = current->next;
	}
	if (wpipe.result == NULL)
		return (tokens);
	return (wpipe.result);
}
