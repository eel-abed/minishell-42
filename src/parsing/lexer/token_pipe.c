/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:43 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/05 16:09:47 by mafourni         ###   ########.fr       */
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
			// free(tmp);
		}
		tmp = cmd_str;
		cmd_str = ft_strjoin(cmd_str, cmd_start->value, gc);
		// free(tmp);
		cmd_start = cmd_start->next;
	}
	return (cmd_str);
}

char	*handle_last_token(char *cmd_str, t_tokens *cmd_start,
		t_tokens *current, t_tokens *tokens, t_garbage **gc)
{
	char	*tmp;

	if (!current->next && current->type != kind_pipe)
	{
		if (cmd_start != tokens || ft_strlen(cmd_str) > 0)
		{
			tmp = cmd_str;
			cmd_str = ft_strjoin(cmd_str, " ", gc);
		}
		tmp = cmd_str;
		cmd_str = ft_strjoin(cmd_str, current->value, gc);
	}
	return (cmd_str);
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
	t_tokens	*current;
	t_tokens	*cmd_start;
	t_tokens	*result;
	t_tokens	*new_token;
	char		*cmd_str;
	int			isEcho;

	if (!tokens)
		return (NULL);
	result = NULL;
	cmd_str = NULL;
	new_token = NULL;
	current = tokens;
	cmd_start = tokens;
	isEcho = 0;
	while (current)
	{
		if (is_echo_cmd(current->value, gc) == 1)
			isEcho = 1;
		if (current->type == kind_pipe || (!current->next && isEcho == 0))
		{
			if (isEcho == 0)
			{
				cmd_str = build_cmd_str(cmd_start, current, tokens, gc);
				cmd_str = handle_last_token(cmd_str, cmd_start, current, tokens,
						gc);
				new_token = mini_lstnew(cmd_str, kind_none, gc);
				mini_lstadd_back(&result, new_token);
				add_pipe_token(&result, &cmd_start, current, gc);
				cmd_start = current->next;
			}
			else
			{
				add_pipe_token(&result, &cmd_start, current, gc);
				cmd_start = current->next;
			}
			isEcho = 0;
		}
		else if (isEcho == 1)
		{
			new_token = mini_lstnew(ft_strdup(current->value, gc),
					current->type, gc);
			mini_lstadd_back(&result, new_token);
			add_pipe_token(&result, &cmd_start, current, gc);
			cmd_start = current->next;
		}
		current = current->next;
	}
	if (result == NULL)
		return (tokens);
	return (result);
}
