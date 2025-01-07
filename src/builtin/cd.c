/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:33:06 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void update_env_vars(t_env *env)
{
    char cwd[PATH_MAX];
    char *oldpwd;
    int i;

    // Find current PWD
    oldpwd = NULL;
    for (i = 0; env->env_array[i]; i++)
    {
        if (strncmp(env->env_array[i], "PWD=", 4) == 0)
        {
            oldpwd = env->env_array[i] + 4;
            break;
        }
    }

    if (oldpwd)
    {
        // Update OLDPWD
        for (i = 0; env->env_array[i]; i++)
        {
            if (strncmp(env->env_array[i], "OLDPWD=", 7) == 0)
            {
                free(env->env_array[i]);
                env->env_array[i] = ft_strjoin("OLDPWD=", oldpwd);
                break;
            }
        }
    }

    // Update PWD
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        for (i = 0; env->env_array[i]; i++)
        {
            if (strncmp(env->env_array[i], "PWD=", 4) == 0)
            {
                free(env->env_array[i]);
                env->env_array[i] = ft_strjoin("PWD=", cwd);
                break;
            }
        }
    }
}

void cd_builtin(char **args, t_env *env)
{
    char *home_dir = NULL;
    int i;

    if (args[1] == NULL)
    {
        // Find HOME in environment
        for (i = 0; env->env_array[i]; i++)
        {
            if (strncmp(env->env_array[i], "HOME=", 5) == 0)
            {
                home_dir = env->env_array[i] + 5;
                break;
            }
        }

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
    else if (chdir(args[1]) != 0)
    {
        perror("cd");
        g_exit_status = 1;
        return;
    }
    update_env_vars(env);
    g_exit_status = 0;
}
