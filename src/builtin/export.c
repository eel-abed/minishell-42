/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:17 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/21 18:23:07 by eel-abed         ###   ########.fr       */
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

static void	update_env_var(t_env_var *var, const char *value)
{
	if (var->value)
		free(var->value);
	if (value)
		var->value = ft_strdup(value);
	else
		var->value = NULL;
}

static void	add_env_var(t_env *env, const char *key, const char *value)
{
	t_env_var	*new_var;

	new_var = malloc(sizeof(t_env_var));
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
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

static void	set_env_var(char *arg, t_env *env)
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
			add_env_var(env, arg, NULL);
		return ;
	}
	key_len = equal_sign - arg;
	key = ft_substr(arg, 0, key_len);
	value = equal_sign + 1;
	if (!key)
		return ;
	existing = find_env_var(env, key);
	if (existing)
		update_env_var(existing, value);
	else
		add_env_var(env, key, value);
	free(key);
}

void export_builtin(t_tokens *tokens, t_env *env)
{
    char **args;
    int i;

    // Split the token value into command and arguments
    args = ft_split(tokens->value, ' ');
    if (!args)
        return;

    i = 1;  // Skip "export" command
    if (!args[1])
    {
        print_exported_vars(env);
        free_paths(args);
        return;
    }

    while (args[i])
    {
        if (ft_isalpha(args[i][0]) || args[i][0] == '_')
            set_env_var(args[i], env);
        else
            handle_export_error(args[i]);
        i++;
    }
    
    free_paths(args);
}
