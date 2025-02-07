/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:17 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:55:58 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_exported_vars(t_env *env)
{
    int i;

    i = 0;
    while (env->env_array[i])
    {
        printf("export %s\n", env->env_array[i]);
        i++;
    }
}

static void set_env_var(char *arg, t_env *env)
{
    char *equal_sign;
    char **new_env;
    int i;

    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        new_env = malloc(sizeof(char *) * (env->size + 2));
        i = 0;
        while (env->env_array[i])
        {
            new_env[i] = ft_strdup(env->env_array[i]);
            i++;
        }
        new_env[i] = ft_strdup(arg);
        new_env[i + 1] = NULL;
        
        // Free old array
        i = 0;
        while (env->env_array[i])
        {
            free(env->env_array[i]);
            i++;
        }
        free(env->env_array);
        
        env->env_array = new_env;
        env->size++;
    }
}

void export_builtin(char **args, t_env *env)
{
    int i;
    char *error_msg;
    char *temp;  // Add this

    i = 1;
    if (!args[1])
    {
        print_exported_vars(env);
        return;
    }
    while (args[i])
    {
        if (ft_isalpha(args[i][0]) || args[i][0] == '_')
        {
            set_env_var(args[i], env);
        }
        else
        {
            error_msg = ft_strjoin("minishell: export: '", args[i]);
            temp = error_msg;  // Store first allocation
            error_msg = ft_strjoin(error_msg, "': not a valid identifier");
            free(temp);  // Free first allocation
            ft_putendl_fd(error_msg, STDERR_FILENO);
            free(error_msg);
        }
        i++;
    }
}
