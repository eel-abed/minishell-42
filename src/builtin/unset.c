/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:48 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 15:02:17 by mafourni         ###   ########.fr       */
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
	t_env_var	*to_free;

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
			to_free = current;
			free(to_free->key);
			free(to_free->value);
			free(to_free);
			env->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int unset_builtin(t_tokens *tokens, t_env *env, t_command *cmd,t_garbage **gc)
{
    char **args;
    int i;
    int exit_status;

    // Split the token value into command and arguments
    args = ft_split(tokens->value, ' ',gc);
    if (!args)
        return (1);

    i = 1;  // Skip "unset" command
    exit_status = 0;
    
    if (!args[i])
    {
        free_paths(args);
        return (0);
    }

    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            exit_status = 1;
        }
        else
            remove_env_var(env, args[i]);
        i++;
    }

    cmd->exit_status = exit_status;
    free_paths(args);
    return (exit_status);
}
