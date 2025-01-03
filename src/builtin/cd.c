/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/03 16:13:54 by eel-abed         ###   ########.fr       */
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

void cd_builtin(char **args)
{
    char *home_dir;

    if (args[1] == NULL)
    {
        home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            g_exit_status = 1;
            return;
        }
        if (chdir(home_dir) != 0)
        {
            perror("cd");
            g_exit_status = 1;
            return;
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
            g_exit_status = 1;
            return;
        }
    }
    update_env_vars();
    g_exit_status = 0;
}
