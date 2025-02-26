/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:41 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/26 18:14:22 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_piped_commands(t_tokens *tokens, t_command *cmd_info, t_garbage **gc)
{
    int cmd_count = 1;
    int pipe_count;
    int **pipes;
    pid_t *pids;
    t_tokens *current = tokens;
    int i, status;

    // Count the number of commands (number of pipes + 1)
    while (current)
    {
        if (current->type == kind_pipe)
            cmd_count++;
        current = current->next;
    }
    
    pipe_count = cmd_count - 1;
    
    // Allocate memory for pipes and pids
    pipes = gc_malloc(gc, sizeof(int*) * pipe_count);
    for (i = 0; i < pipe_count; i++)
        pipes[i] = gc_malloc(gc, sizeof(int) * 2);
    pids = gc_malloc(gc, sizeof(pid_t) * cmd_count);
    
    if (!pipes || !pids)
    {
        ft_putstr_fd("minishell: memory allocation error\n", 2);
        return;
    }
    
    // Create all pipes
    for (i = 0; i < pipe_count; i++)
    {
        if (pipe(pipes[i]) < 0)
        {
            perror("pipe");
            return;
        }
    }
    
    // Execute each command
    current = tokens;
    for (i = 0; i < cmd_count; i++)
    {
        // Skip pipe tokens to get to the next command
        if (i > 0)
        {
            while (current && current->type != kind_pipe)
                current = current->next;
            if (current)
                current = current->next;
        }
        
        if (!current)
            break;
        
        pids[i] = fork();
        if (pids[i] < 0)
        {
            perror("fork");
            return;
        }
        
        if (pids[i] == 0) // Child process
        {
            // Set up pipe redirections
            
            // If not first command, set stdin to read from previous pipe
            if (i > 0)
            {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }
            
            // If not last command, set stdout to write to next pipe
            if (i < pipe_count)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            
            // Close all pipe fds in child
            for (int j = 0; j < pipe_count; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            
            // Execute the command
            execute_command(current, cmd_info, gc);
            exit(cmd_info->exit_status);
        }
    }
    
    // Close all pipe fds in parent
    for (i = 0; i < pipe_count; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Wait for all children
    for (i = 0; i < cmd_count; i++)
    {
        waitpid(pids[i], &status, 0);
        
        // The exit status of the last command is the exit status
        // of the whole pipeline
        if (i == cmd_count - 1)
        {
            if (WIFEXITED(status))
                cmd_info->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                cmd_info->exit_status = 128 + WTERMSIG(status);
        }
    }
}
