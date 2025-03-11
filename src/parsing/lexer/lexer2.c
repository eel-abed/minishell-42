/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:56 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/11 17:19:54 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	t_env_var *head;
	char *new_input;

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
