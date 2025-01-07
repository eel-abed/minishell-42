/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:09:14 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:28:07 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env *init_env(char **envp) {
    t_env *env;
    int i;

    env = malloc(sizeof(t_env));
    if (!env)
        return NULL;

    // Count environment variables
    for (i = 0; envp[i]; i++)
        ;
    
    env->size = i;
    env->env_array = malloc(sizeof(char *) * (i + 1));
    if (!env->env_array) {
        free(env);
        return NULL;
    }

    // Copy environment variables
    i = 0;
    while (envp[i]) {
        env->env_array[i] = ft_strdup(envp[i]);
        i++;
    }
    env->env_array[i] = NULL;
    return env;
}

void free_env(t_env *env) {
    int i;

    if (!env)
        return;
    
    for (i = 0; env->env_array[i]; i++)
        free(env->env_array[i]);
    free(env->env_array);
    free(env);
}
