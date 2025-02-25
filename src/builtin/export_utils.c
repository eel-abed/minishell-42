/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:50:47 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 18:08:12 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_env_var(t_env *env, t_env_var *new_var)
{
	t_env_var	*current;

	if (!env->vars)
	{
		env->vars = new_var;
		return ;
	}
	current = env->vars;
	while (current->next)
		current = current->next;
	current->next = new_var;
}

void	handle_export_error(char *arg,t_garbage **gc)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin("minishell: export: '", arg,gc);
	temp = error_msg;
	error_msg = ft_strjoin(error_msg, "': not a valid identifier",gc);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}
