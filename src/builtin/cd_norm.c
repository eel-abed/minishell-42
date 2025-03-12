/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:32:19 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 11:38:17 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	validate_cd_args(char **args, t_command *cmd)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		cmd->exit_status = 1;
		return (false);
	}
	return (true);
}

void	display_pwd_if_needed(char **args, t_env *env)
{
	t_env_var	*pwd_var;

	if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		pwd_var = find_env_var(env, "PWD");
		if (pwd_var && pwd_var->value)
		{
			ft_putstr_fd(pwd_var->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
}

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

const char	*handle_home_directory(t_env *env, t_command *cmd)
{
	t_env_var	*home_var;

	home_var = find_env_var(env, "HOME");
	if (!home_var || !home_var->value)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		cmd->exit_status = 1;
		return (NULL);
	}
	return (home_var->value);
}
