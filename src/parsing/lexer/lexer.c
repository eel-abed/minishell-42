/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 19:10:17 by mafourni         ###   ########.fr       */
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
	token_list = lets_tokeninze(temp, gc);
	token_list = ft_trim_all(token_list, gc);
	token_list = token_with_pipe(token_list, gc);
	current = token_list;
	while (current)
	{
		current->env = env;
		current = current->next;
	}
	return (token_list);
}

char	*replace_null(char *input, int j, char *tmp, t_garbage **gc)
{
	char	*new_input;
	int		len;

	len = ft_strlen(input);
	new_input = ft_calloc(len + 1, 1, gc);
	if (!new_input)
		return (NULL);
	new_input = ft_strncpy(new_input, input, j - 1);
	ft_strlcat(new_input, input + ft_strlen(tmp) + j, len + 1);
	input = new_input;
	return (input);
}

static char	*handle_env_value(t_env *env, t_might replace_mr, char *tmp,
		t_garbage **gc)
{
	char	*new_input;
	int		len;

	if (!env->vars->value)
	{
		len = ft_strlen(replace_mr.input) - (ft_strlen(tmp) + 1);
		new_input = ft_calloc(len + 1, 1, gc);
		ft_strncpy(new_input, replace_mr.input, replace_mr.j - 1);
		ft_strlcat(new_input, replace_mr.input + replace_mr.j + ft_strlen(tmp),
			len + 1);
	}
	else
	{
		len = ft_strlen(replace_mr.input) + ft_strlen(env->vars->value);
		new_input = ft_calloc(len + 1, 1, gc);
		new_input = ft_strncpy(new_input, replace_mr.input, replace_mr.j);
		ft_strlcat_mini(new_input, env->vars->value, len);
		ft_strlcat(new_input, replace_mr.input + replace_mr.j + ft_strlen(tmp),
			len);
	}
	return (new_input);
}

char	*might_replace(t_env *env, t_might replace_mr, char *tmp,
		t_garbage **gc)
{
	t_env_var	*head;
	char		*new_input;

	new_input = replace_mr.input;
	head = env->vars;
	while (env->vars != NULL)
	{
		if (ft_strcmp(env->vars->key, tmp) == 0)
		{
			new_input = handle_env_value(env, replace_mr, tmp, gc);
			replace_mr.input = new_input;
			env->vars = head;
			break ;
		}
		env->vars = env->vars->next;
	}
	if (env->vars == NULL)
	{
		replace_mr.input = replace_null(replace_mr.input, replace_mr.j, tmp,
				gc);
		env->vars = head;
	}
	return (replace_mr.input);
}
