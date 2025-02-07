/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-07 18:44:16 by eel-abed          #+#    #+#             */
/*   Updated: 2025-02-07 18:44:16 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void free_env_array(char **env_array)
{
    int i;

    if (!env_array)
        return;
    i = 0;
    while (env_array[i])
    {
        free(env_array[i]);
        i++;
    }
    free(env_array);
}

void update_env_array(t_env *env)
{
    t_env_var *current;
    int i;
    char *tmp;

    if (!env)
        return;
    
    // Free existing array if it exists
    if (env->env_array)
        free_env_array(env->env_array);
    
    // Allocate new array
    env->env_array = malloc(sizeof(char *) * (env->size + 1));
    if (!env->env_array)
        return;
    
    // Fill array
    current = env->vars;
    i = 0;
    while (current)
    {
        // Allocate space for "key=value\0"
        tmp = malloc(ft_strlen(current->key) + ft_strlen(current->value) + 2);
        if (!tmp)
        {
            free_env_array(env->env_array);
            env->env_array = NULL;
            return;
        }
        
        // Create "key=value" string
        ft_strlcpy(tmp, current->key, ft_strlen(current->key) + 1);
        ft_strlcat(tmp, "=", ft_strlen(current->key) + 2);
        ft_strlcat(tmp, current->value, ft_strlen(current->key) + ft_strlen(current->value) + 2);
        
        env->env_array[i++] = tmp;
        current = current->next;
    }
    env->env_array[i] = NULL;
}
