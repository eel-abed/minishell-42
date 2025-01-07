/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:41 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:56:08 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void child_process_first(t_command *cmd_info)
{
    char *cmd_path;
    
    close(cmd_info->pipefd[0]);
    dup2(cmd_info->pipefd[1], STDOUT_FILENO);
    close(cmd_info->pipefd[1]);
    if (is_builtin(cmd_info->cmd1[0]))
        execute_builtin(cmd_info->cmd1[0], cmd_info->cmd1, cmd_info);
    else
    {
        cmd_path = find_command_path(cmd_info->cmd1[0], cmd_info->env);
        if (!cmd_path)
        {
            write(2, cmd_info->cmd1[0], ft_strlen(cmd_info->cmd1[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }
        execve(cmd_path, cmd_info->cmd1, cmd_info->env->env_array);
        free(cmd_path);
        exit(126);
    }
}

static void child_process_second(t_command *cmd_info)
{
    char *cmd_path;
    
    close(cmd_info->pipefd[1]);
    dup2(cmd_info->pipefd[0], STDIN_FILENO);
    close(cmd_info->pipefd[0]);
    if (is_builtin(cmd_info->cmd2[0]))
        execute_builtin(cmd_info->cmd2[0], cmd_info->cmd2, cmd_info);
    else
    {
        cmd_path = find_command_path(cmd_info->cmd2[0], cmd_info->env);
        if (!cmd_path)
        {
            write(2, cmd_info->cmd2[0], ft_strlen(cmd_info->cmd2[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }
        execve(cmd_path, cmd_info->cmd2, cmd_info->env->env_array);
        free(cmd_path);
        exit(126);
    }
}

pid_t	fork_and_execute_first(t_command *cmd_info)
{
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
        child_process_first(cmd_info);
    return (pid);
}

pid_t	fork_and_execute_second(t_command *cmd_info)
{
    pid_t	pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
        child_process_second(cmd_info);
    return (pid);
}
