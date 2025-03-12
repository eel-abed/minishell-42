/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:52:49 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 12:01:44 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_echo_block(t_tokens **current, t_wpipe_norm *wpipe,
		t_garbage **gc)
{
	while (*current && (*current)->type != kind_pipe)
	{
		wpipe->new_token = mini_lstnew(ft_strdup((*current)->value, gc),
				(*current)->type, gc);
		mini_lstadd_back(&wpipe->result, wpipe->new_token);
		*current = (*current)->next;
	}
}

void	process_non_echo_block(t_tokens **current, t_wpipe_norm *wpipe,
		t_garbage **gc)
{
	wpipe->new_token = mini_lstnew(ft_strdup(" ", gc), kind_none, gc);
	while (*current && (*current)->type != kind_pipe)
	{
		wpipe->new_token->value = ft_strjoin(wpipe->new_token->value,
				(*current)->value, gc);
		if ((*current)->next)
			wpipe->new_token->value = ft_strjoin(wpipe->new_token->value, " ",
					gc);
		*current = (*current)->next;
	}
	mini_lstadd_back(&wpipe->result, wpipe->new_token);
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
			process_echo_block(&current, &wpipe, gc);
		else
			process_non_echo_block(&current, &wpipe, gc);
		if (current && current->type == kind_pipe)
			add_pipe_token(&wpipe.result, &wpipe.cmd_start, current, gc);
		if (current)
			current = current->next;
	}
	if (wpipe.result == NULL)
		return (tokens);
	return (wpipe.result);
}
