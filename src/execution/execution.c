/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/18 14:01:50 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
        || ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
        || ft_strcmp(cmd, "exit") == 0)
        return (true);
    return (false);
}   
