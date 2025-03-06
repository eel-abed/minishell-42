/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/05 18:51:23 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*find_env_var(t_env *env, const char *key)
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

static void	update_env_var(t_env *env, const char *key, const char *value,
		t_garbage **gc)
{
	t_env_var	*var;
	t_env_var	*new_var;

	var = find_env_var(env, key);
	if (var)
		var->value = ft_strdup(value, gc);
	else
	{
		new_var = gc_malloc(gc, sizeof(t_env_var));
		if (!new_var)
			return ;
		new_var->key = ft_strdup(key, gc);
		new_var->value = ft_strdup(value, gc);
		new_var->next = env->vars;
		env->vars = new_var;
		env->size++;
	}
}

void	update_env_vars(t_env *env, t_garbage **gc)
{
	char		cwd[PATH_MAX];
	t_env_var	*pwd_var;

	pwd_var = find_env_var(env, "PWD");
	if (pwd_var && pwd_var->value)
		update_env_var(env, "OLDPWD", pwd_var->value, gc);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_env_var(env, "PWD", cwd, gc);
}

static const char	*get_target_directory(char **args, t_env *env,
		t_command *cmd)
{
	t_env_var	*home_var;

	if (!args[1])
	{
		home_var = find_env_var(env, "HOME");
		if (!home_var || !home_var->value)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			cmd->exit_status = 1;
			return (NULL);
		}
		return (home_var->value);
	}
	return (args[1]);
}

void	cd_builtin(t_tokens *tokens, t_env *env, t_command *cmd, t_garbage **gc)
{
	char		**args;
	const char	*target_dir;

	args = ft_split(tokens->value, ' ', gc);
	if (!args)
		return ;
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		cmd->exit_status = 1;
		return ;
	}
	target_dir = get_target_directory(args, env, cmd);
	if (!target_dir)
		return ;
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		cmd->exit_status = 1;
		return ;
	}
	update_env_vars(env, gc);
	cmd->exit_status = 0;
}
