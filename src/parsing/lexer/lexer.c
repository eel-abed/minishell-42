/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 15:53:41 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_syntax(char *input, t_command *cmd)
{
	size_t			i;
	size_t			len;
	t_operator_kind	maybe_kind;

	maybe_kind = kind_none;
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (is_operator(input[i], &maybe_kind))
		{
			if (is_valid_operator(&input[i], len - i, maybe_kind) == false)
			{
				cmd->exit_status = 2;
				return (false);
			}
		}
		++i;
	}
	return (true);
}

t_tokens	*ft_lexer(char *input, t_env *env, t_garbage **gc, t_command *cmd)
{
	t_tokens	*token_list;
	char		*temp;
	t_tokens	*current;

	temp = input;
	token_list = NULL;
	add_history(input);
	if (quote_check(temp, cmd) == 1)
		return (printf("Syntax %s !\n", ERROR), NULL);
	if (check_syntax(temp, cmd) == 0)
		return (printf("OPE %s !\n", ERROR), NULL);
	temp = any_env(temp, env, gc, cmd);
	print_tokens(token_list);
	token_list = lets_tokeninze(temp, gc);
	print_tokens(token_list);
	token_list = ft_trim_all(token_list, gc);
	print_tokens(token_list);
	token_list = add_quotes_cat(token_list, gc);
	print_tokens(token_list);
	token_list = token_with_pipe(token_list, gc);
	current = token_list;
	while (current)
	{
		current->env = env;
		current = current->next;
	}
	return (token_list);
}

static bool	is_first_command_echo(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == kind_none)
			return (ft_strcmp(tokens->value, "echo") == 0);
		tokens = tokens->next;
	}
	return (false);
}

static void	quote_token_if_needed(t_tokens *current, t_garbage **gc,
		bool is_echo_cmd)
{
	t_tokens	*next;
	char		*quoted;

	if (current->value && (ft_strcmp(current->value, "cat") == 0
			|| ft_strcmp(current->value, "ls") == 0 || ft_strcmp(current->value,
				"<") == 0 || (ft_strcmp(current->value, ">") == 0
				&& !is_echo_cmd)))
	{
		next = current->next;
		if (next && next->type == kind_none)
		{
			if (next->value[0] != '"' && next->value[0] != '\'')
			{
				quoted = ft_strjoin("\"", next->value, gc);
				next->value = ft_strjoin(quoted, "\"", gc);
			}
		}
	}
}

t_tokens	*add_quotes_cat(t_tokens *tokens, t_garbage **gc)
{
	t_tokens	*current;
	bool		is_echo_cmd;
	bool		first_command_is_echo;

	current = tokens;
	is_echo_cmd = false;
	first_command_is_echo = is_first_command_echo(tokens);
	while (current)
	{
		if (current->value && ft_strcmp(current->value, "echo") == 0)
			is_echo_cmd = true;
		if (!first_command_is_echo)
			quote_token_if_needed(current, gc, is_echo_cmd);
		if (current->value && ft_strcmp(current->value, "|") == 0)
			is_echo_cmd = false;
		current = current->next;
	}
	return (tokens);
}
