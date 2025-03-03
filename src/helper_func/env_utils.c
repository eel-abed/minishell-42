/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:09:14 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/03 15:08:54 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_array(t_env *env, t_garbage **gc)
{
	char		**array;
	t_env_var	*current;
	int			i;

	array = gc_malloc(gc, sizeof(char *) * (env->size + 1));
	if (!array)
		return (NULL);
	current = env->vars;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			array[i] = join_env_var(current, gc);
			if (!array[i++])
				return (NULL);
		}
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

static t_env_var	*create_env_var(const char *env_str, t_garbage **gc)
{
	t_env_var	*var;
	char		*equals;
	size_t		key_len;

	var = init_env_var(gc);
	if (!var)
		return (NULL);
	equals = ft_strchr(env_str, '=');
	if (!equals)
	{
		var->key = ft_strdup(env_str, gc);
		var->value = NULL;
		return (var);
	}
	key_len = equals - env_str;
	var->key = ft_substr(env_str, 0, key_len, gc);
	var->value = ft_strdup(equals + 1, gc);
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	return (var);
}

static void	append_env_var_to_env(t_env *env, t_env_var *new_var)
{
	t_env_var	*current;

	if (!env->vars)
		env->vars = new_var;
	else
	{
		current = env->vars;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
	env->size++;
}

static t_env	*init_empty_env(t_garbage **gc)
{
	t_env	*env;

	env = gc_malloc(gc, sizeof(t_env));
	if (!env)
		return (NULL);
	env->vars = NULL;
	env->size = 0;
	return (env);
}

t_env	*init_env(char **envp, t_garbage **gc)
{
	t_env		*env;
	t_env_var	*new_var;
	int			i;

	env = init_empty_env(gc);
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_var = create_env_var(envp[i], gc);
		if (!new_var)
		{
			free_env(env);
			return (NULL);
		}
		append_env_var_to_env(env, new_var);
		i++;
	}
	return (env);
}
