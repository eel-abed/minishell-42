/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:07:14 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/03 15:08:11 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_env_var(t_env_var *current, t_garbage **gc)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(current->key, "=", gc);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, current->value, gc);
	return (result);
}

t_env_var	*init_env_var(t_garbage **gc)
{
	t_env_var	*var;

	var = gc_malloc(gc, sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->next = NULL;
	return (var);
}

void	free_env(t_env *env)
{
	t_env_var	*current;
	t_env_var	*next;

	if (!env)
		return ;
	current = env->vars;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(env);
}
