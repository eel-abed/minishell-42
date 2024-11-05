/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:17 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/05 13:40:01 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	print_exported_vars(void)
{
	char		**env;

	env = environ;
	while (*env)
	{
		printf("export %s\n", *env);
		env++;
	}
}

static	void	set_env_var(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		setenv(arg, equal_sign + 1, 1);
	}
	else
	{
		setenv(arg, "", 1);
	}
}

void	export_builtin(char **args)
{
	int		i;
	char	*error_msg;

	i = 1;
	if (!args[1])
	{
		print_exported_vars();
		return ;
	}
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) || args[i][0] == '_')
		{
			set_env_var(args[i]);
		}
		else
		{
			error_msg = ft_strjoin("minishell: export: '", args[i]);
			error_msg = ft_strjoin(error_msg, "': not a valid identifier");
			ft_putendl_fd(error_msg, STDERR_FILENO);
			free(error_msg);
		}
		i++;
	}
}
