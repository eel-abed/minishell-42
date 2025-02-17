/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/17 17:21:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env_var	*find_env_var(t_env *env, const char *key)
{
	t_env_var	*current;
	size_t		key_len;

	if (!key)
		return (NULL);
	key_len = ft_strlen(key);
	current = env->vars;
	while (current)
	{
		if (ft_strlen(current->key) == key_len && ft_strncmp(current->key, key,
				key_len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static void	update_env_var(t_env *env, const char *key, const char *value)
{
	t_env_var	*var;
	t_env_var	*new_var;

	var = find_env_var(env, key);
	if (var)
	{
		if (var->value)
			free(var->value);
		var->value = ft_strdup(value);
	}
	else
	{
		new_var = malloc(sizeof(t_env_var));
		if (!new_var)
			return ;
		new_var->key = ft_strdup(key);
		new_var->value = ft_strdup(value);
		new_var->next = env->vars;
		env->vars = new_var;
		env->size++;
	}
}

void	update_env_vars(t_env *env)
{
	char		cwd[PATH_MAX];
	t_env_var	*pwd_var;

	pwd_var = find_env_var(env, "PWD");
	if (pwd_var && pwd_var->value)
		update_env_var(env, "OLDPWD", pwd_var->value);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(env, "PWD", cwd);
}

void	cd_builtin(char **args, t_env *env, t_command *cmd)
{
	t_env_var	*home_var;
	const char	*target_dir;

	if (!args[1])
	{
		home_var = find_env_var(env, "HOME");
		if (!home_var || !home_var->value)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			cmd->exit_status = 1;
			return ;
		}
		target_dir = home_var->value;
	}
	else
		target_dir = args[1];
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		cmd->exit_status = 1;
		return ;
	}
	update_env_vars(env);
	cmd->exit_status = 0;
}
