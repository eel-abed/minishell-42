/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:53:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/09 17:54:47 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_child(pid_t pid)
{
	int	status;
	int	exit_status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else
		exit_status = 1;
	return (exit_status);
}

t_env_var	*get_path_variable(t_env *env)
{
	t_env_var	*path_var;

	if (!env)
	{
		return (NULL);
	}
	if (!env->vars)
	{
		return (NULL);
	}
	path_var = env->vars;
	while (path_var)
	{
		if (path_var->key && ft_strncmp(path_var->key, "PATH", 4) == 0)
			return (path_var);
		path_var = path_var->next;
	}
	return (NULL);
}
