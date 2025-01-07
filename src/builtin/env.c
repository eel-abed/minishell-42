/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:40 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:31:54 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void env_builtin(t_env *env)
{
    int i;

    i = 0;
    while (env->env_array[i])
    {
        ft_putendl_fd(env->env_array[i], STDOUT_FILENO);
        i++;
    }
}
