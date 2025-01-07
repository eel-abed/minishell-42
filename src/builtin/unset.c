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

void unset_builtin(char **args, t_env *env)
{
    int i, j, k;

    i = 1;
    while (args[i])
    {
        j = 0;
        while (env->env_array[j])
        {
            if (strncmp(env->env_array[j], args[i], strlen(args[i])) == 0
                && env->env_array[j][strlen(args[i])] == '=')
            {
                free(env->env_array[j]);
                k = j;
                while (env->env_array[k])
                {
                    env->env_array[k] = env->env_array[k + 1];
                    k++;
                }
                env->size--;
                break;
            }
            j++;
        }
        i++;
    }
}
