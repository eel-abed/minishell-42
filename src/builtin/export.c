/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:17 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/07 18:50:29 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_exported_vars(t_env *env)
{
    t_env_var *current;

    current = env->vars;
    while (current)
    {
        ft_putstr_fd("export ", STDOUT_FILENO);
        ft_putstr_fd(current->key, STDOUT_FILENO);
        if (current->value)
        {
            ft_putchar_fd('=', STDOUT_FILENO);
            ft_putchar_fd('"', STDOUT_FILENO);
            ft_putstr_fd(current->value, STDOUT_FILENO);
            ft_putchar_fd('"', STDOUT_FILENO);
        }
        ft_putchar_fd('\n', STDOUT_FILENO);
        current = current->next;
    }
}

static t_env_var *find_env_var(t_env *env, const char *key)
{
    t_env_var *current;

    current = env->vars;
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

static void update_env_var(t_env_var *var, const char *value)
{
    if (var->value)
        free(var->value);
    var->value = value ? ft_strdup(value) : NULL;
}

static void add_env_var(t_env *env, const char *key, const char *value)
{
    t_env_var *new_var;
    t_env_var *current;

    new_var = malloc(sizeof(t_env_var));
    if (!new_var)
        return;

    new_var->key = ft_strdup(key);
    new_var->value = value ? ft_strdup(value) : NULL;
    new_var->next = NULL;

    if (!new_var->key || (value && !new_var->value))
    {
        free(new_var->key);
        free(new_var->value);
        free(new_var);
        return;
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
}

static void set_env_var(char *arg, t_env *env)
{
    char *equal_sign;
    char *key;
    char *value;
    t_env_var *existing;
    size_t key_len;

    equal_sign = ft_strchr(arg, '=');
    if (!equal_sign)
    {
        existing = find_env_var(env, arg);
        if (!existing)
            add_env_var(env, arg, NULL);
        return;
    }

    key_len = equal_sign - arg;
    key = ft_substr(arg, 0, key_len);
    value = equal_sign + 1;

    if (!key)
        return;

    existing = find_env_var(env, key);
    if (existing)
        update_env_var(existing, value);
    else
        add_env_var(env, key, value);

    free(key);
}

void export_builtin(char **args, t_env *env)
{
    int i;
    char *error_msg;
    char *temp;

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
            temp = error_msg;
            error_msg = ft_strjoin(error_msg, "': not a valid identifier");
            free(temp);
            ft_putendl_fd(error_msg, STDERR_FILENO);
            free(error_msg);
        }
        i++;
    }
}
