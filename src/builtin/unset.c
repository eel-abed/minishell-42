/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:48 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 17:53:41 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_identifier(const char *str)
{
	if (!str || !*str || ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static void	remove_env_var(t_env *env, const char *key)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = env->vars;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env->vars = current->next;
			env->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	process_unset_args(char **args, t_env *env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (!args[i])
		return (0);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
			remove_env_var(env, args[i]);
		i++;
	}
	return (exit_status);
}

int	unset_builtin(t_tokens *tokens, t_env *env, t_command *cmd, t_garbage **gc)
{
	char	**args;
	int		exit_status;

	args = ft_split(tokens->value, ' ', gc);
	if (!args)
		return (1);
	exit_status = process_unset_args(args, env);
	cmd->exit_status = exit_status;
	return (exit_status);
}
