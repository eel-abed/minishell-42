/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:48 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:32:31 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int is_valid_identifier(const char *str)
{
    if (!str || !*str || ft_isdigit(*str))
        return (0);
    
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static void remove_env_var(t_env *env, int index)
{
    int k;

    free(env->env_array[index]);
    k = index;
    while (env->env_array[k])
    {
        env->env_array[k] = env->env_array[k + 1];
        k++;
    }
    env->size--;
}

int unset_builtin(char **args, t_env *env)
{
    int i;
    int j;
    int exit_status;

    i = 1;
    exit_status = 0;
    if (!args[i])
        return (0);

    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            exit_status = 1;
        }
        else
        {
            j = 0;
            while (env->env_array[j])
            {
                if (strncmp(env->env_array[j], args[i], strlen(args[i])) == 0
                    && env->env_array[j][strlen(args[i])] == '=')
                {
                    remove_env_var(env, j);
                    break;
                }
                j++;
            }
        }
        i++;
    }
    return (exit_status);
}
