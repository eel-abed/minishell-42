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

char **env_to_array(t_env *env)
{
    char **array;
    t_env_var *current;
    char *temp;
    int i;

    array = malloc(sizeof(char *) * (env->size + 1));
    if (!array)
        return NULL;

    current = env->vars;
    i = 0;
    while (current)
    {
        if (current->value)
        {
            temp = ft_strjoin(current->key, "=");
            if (!temp)
            {
                while (--i >= 0)
                    free(array[i]);
                free(array);
                return NULL;
            }
            array[i] = ft_strjoin(temp, current->value);
            free(temp);
            if (!array[i])
            {
                while (--i >= 0)
                    free(array[i]);
                free(array);
                return NULL;
            }
            i++;
        }
        current = current->next;
    }
    array[i] = NULL;
    return array;
}

static t_env_var *create_env_var(const char *env_str)
{
    t_env_var *var;
    char *equals;
    size_t key_len;

    var = malloc(sizeof(t_env_var));
    if (!var)
        return NULL;

    equals = ft_strchr(env_str, '=');
    if (!equals)
    {
        var->key = ft_strdup(env_str);
        var->value = NULL;
    }
    else
    {
        key_len = equals - env_str;
        var->key = ft_substr(env_str, 0, key_len);
        var->value = ft_strdup(equals + 1);
        if (!var->key || !var->value)
        {
            free(var->key);
            free(var->value);
            free(var);
            return NULL;
        }
    }
    var->next = NULL;
    return var;
}

t_env *init_env(char **envp)
{
    t_env *env;
    t_env_var *current;
    t_env_var *new_var;
    int i;

    env = malloc(sizeof(t_env));
    if (!env)
        return NULL;

    env->vars = NULL;
    env->size = 0;

    i = 0;
    while (envp[i])
    {
        new_var = create_env_var(envp[i]);
        if (!new_var)
        {
            free_env(env);
            return NULL;
        }

        if (!env->vars)
            env->vars = new_var;
        else
        {
            current = env->vars;
            while (current->next)
                current = current->next;
            current->next = new_var;
        }
        env->size++;
        i++;
    }
    return env;
}

void free_env(t_env *env)
{
    t_env_var *current;
    t_env_var *next;

    if (!env)
        return;

    current = env->vars;
    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(env);
}
