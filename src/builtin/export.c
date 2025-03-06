/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:17 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/06 16:12:43 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_exported_vars(t_env *env)
{
	t_env_var	*current;

	current = env->vars;
	while (current)
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		current = current->next;
	}
}

static void	update_env_var(t_env_var *var, const char *value, t_garbage **gc)
{
	if (value)
		var->value = ft_strdup(value, gc);
	else
		var->value = NULL;
}

static void	add_env_var(t_env *env, const char *key, const char *value,
		t_garbage **gc)
{
	t_env_var	*new_var;

	new_var = gc_malloc(gc, sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key, gc);
	if (value)
		new_var->value = ft_strdup(value, gc);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	if (!new_var->key || (value && !new_var->value))
	{
		free(new_var->key);
		free(new_var->value);
		free(new_var);
		return ;
	}
	append_env_var(env, new_var);
	env->size++;
}

void	set_env_var(char *arg, t_env *env, t_garbage **gc)
{
	char		*equal_sign;
	char		*key;
	char		*value;
	t_env_var	*existing;
	size_t		key_len;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		existing = find_env_var(env, arg);
		if (!existing)
			add_env_var(env, arg, NULL, gc);
		return ;
	}
	key_len = equal_sign - arg;
	key = ft_substr(arg, 0, key_len, gc);
	value = equal_sign + 1;
	if (!key)
		return ;
	existing = find_env_var(env, key);
	if (existing)
		update_env_var(existing, value, gc);
	else
		add_env_var(env, key, value, gc);
}

void	export_builtin(t_tokens *tokens, t_env *env, t_garbage **gc,
		t_command *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = split_mini(tokens->value, gc);
	while (args[i])
	{
		i++;
	}
	if (!args)
		return ;
	i = 1;
	if (!args[1])
	{
		print_exported_vars(env);
		return ;
	}
	while (args[i])
	{
		process_export_arg(args[i], env, gc, cmd);
		i++;
	}
}
