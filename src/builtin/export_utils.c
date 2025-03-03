/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:50:47 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/03 16:45:03 by eel-abed         ###   ########.fr       */
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

void	handle_export_error(char *arg, t_garbage **gc)
{
	char	*error_msg;
	char	*temp;

	error_msg = ft_strjoin("minishell: export: '", arg, gc);
	temp = error_msg;
	error_msg = ft_strjoin(error_msg, "': not a valid identifier", gc);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

static int	is_valid_identifier_name(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	process_export_arg(char *arg, t_env *env, t_garbage **gc, t_command *cmd)
{
	char	*unquoted_arg;

	unquoted_arg = remove_outer_quotes(arg, gc);
	if (!unquoted_arg)
		return ;
	if (is_valid_identifier_name(unquoted_arg))
		set_env_var(unquoted_arg, env, gc);
	else
	{
		handle_export_error(unquoted_arg, gc);
		cmd->exit_status = 1;
	}
}
