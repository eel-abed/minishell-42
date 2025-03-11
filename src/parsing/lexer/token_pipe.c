/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:43 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/11 16:09:22 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*build_cmd_str(t_tokens *cmd_start, t_tokens *current, t_tokens *tokens,
		t_garbage **gc)
{
	char	*cmd_str;

	cmd_str = ft_strdup("", gc);
	while (cmd_start != current)
	{
		if (cmd_start != tokens)
		{
			cmd_str = ft_strjoin(cmd_str, " ", gc);
		}
		cmd_str = ft_strjoin(cmd_str, cmd_start->value, gc);
		cmd_start = cmd_start->next;
	}
	return (cmd_str);
}

char	*handle_last_token(t_wpipe_norm wpipe, t_tokens *current,
		t_tokens *tokens, t_garbage **gc)
{
	if (!current->next && current->type != kind_pipe)
	{
		if (wpipe.cmd_start != tokens || ft_strlen(wpipe.cmd_str) > 0)
		{
			wpipe.cmd_str = ft_strjoin(wpipe.cmd_str, " ", gc);
		}
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

bool	is_echo_block(t_tokens *current, t_garbage **gc)
{
	t_tokens	*tmp;

	tmp = current;
	while (tmp && tmp->type != kind_pipe)
	{
		if (is_echo_cmd(tmp->value, gc) == 1)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_tokens	*token_with_pipe(t_tokens *tokens, t_garbage **gc)
{
	t_tokens		*current;
	t_wpipe_norm	wpipe;

	if (!tokens)
		return (NULL);
	wpipe.result = NULL;
	wpipe.cmd_str = NULL;
	wpipe.new_token = NULL;
	current = tokens;
	wpipe.cmd_start = tokens;
	while (current)
	{
		if (is_echo_block(current, gc))
		{
			while (current && current->type != kind_pipe)
			{
				wpipe.new_token = mini_lstnew(ft_strdup(current->value, gc),
						current->type, gc);
				mini_lstadd_back(&wpipe.result, wpipe.new_token);
				current = current->next;
			}
		}
		else
		{
			wpipe.new_token = mini_lstnew(ft_strdup(" ", gc), kind_none, gc);
			while (current && current->type != kind_pipe)
			{
				wpipe.new_token->value = ft_strjoin(wpipe.new_token->value,
						current->value, gc);
				if (current->next)
					wpipe.new_token->value = ft_strjoin(wpipe.new_token->value,
							" ", gc);
				current = current->next;
			}
			mini_lstadd_back(&wpipe.result, wpipe.new_token);
		}
		if (current)
		{
			if (current->type == kind_pipe)
				add_pipe_token(&wpipe.result, &wpipe.cmd_start, current, gc);
			current = current->next;
		}
	}
	if (wpipe.result == NULL)
		return (tokens);
	return (wpipe.result);
}
