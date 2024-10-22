/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/22 16:52:02 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env_vars(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = getenv("PWD");
	if (oldpwd != NULL)
		setenv("OLDPWD", oldpwd, 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		setenv("PWD", cwd, 1);
	else
		perror("getcwd");
}

void	cd_builtin(char **args)
{
	char	*home_dir;

	if (args[1] == NULL)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return ;
		}
	}
	update_env_vars();
}
