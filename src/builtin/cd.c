/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:19:24 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/07 16:58:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//bug a regler avec cd ecole 42 les espaces sont non geree
void update_env_vars(t_env *env)
{
    char cwd[PATH_MAX];
    char *oldpwd;
    int i;

    // Find current PWD
    oldpwd = NULL;
    i = 0;
    while (env->env_array[i])
    {
        if (strncmp(env->env_array[i], "PWD=", 4) == 0)
        {
            oldpwd = env->env_array[i] + 4;
            break;
        }
        i++;    
    }

    if (oldpwd)
    {
        // Update OLDPWD
        i = 0;
        while (env->env_array[i])
        {
            if (strncmp(env->env_array[i], "OLDPWD=", 7) == 0)
            {
                free(env->env_array[i]);
                env->env_array[i] = ft_strjoin("OLDPWD=", oldpwd);
                break;
            }
            i++;
        }
    }

    // Update PWD
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        i = 0;
        while (env->env_array[i])
        {
            if (strncmp(env->env_array[i], "PWD=", 4) == 0)
            {
                free(env->env_array[i]);
                env->env_array[i] = ft_strjoin("PWD=", cwd);
                break;
            }
            i++;
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
        i = 0;
        while (env->env_array[i])
        {
            if (strncmp(env->env_array[i], "HOME=", 5) == 0)
            {
                home_dir = env->env_array[i] + 5;
                break;
            }
            i++;
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
