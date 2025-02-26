/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:41 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/26 17:40:08 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_piped_commands(t_tokens *tokens, t_command *cmd_info, t_garbage **gc)
{
    t_tokens *cmd1;
    t_tokens *cmd2;
    pid_t pid1, pid2;
    int pipefd[2];
    int status1, status2;
    
    // Find the pipe token
    cmd1 = tokens;
    cmd2 = NULL;
    
    while (tokens)
    {
        if (tokens->type == kind_pipe)
        {
            cmd2 = tokens->next;
            break;
        }
        tokens = tokens->next;
    }
    
    if (!cmd2)
        return; // Error: no second command after pipe
    
    // Create pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        cmd_info->exit_status = 1;
        return;
    }
    
    // First command (writes to pipe)
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("fork");
        cmd_info->exit_status = 1;
        return;
    }
    
    if (pid1 == 0) // Child process for first command
    {
        // Close read end of pipe
        close(pipefd[0]);
        
        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Execute first command
        execute_command(cmd1, cmd_info, gc);
        exit(cmd_info->exit_status);
    }
    
    // Second command (reads from pipe)
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("fork");
        cmd_info->exit_status = 1;
        return;
    }
    
    if (pid2 == 0) // Child process for second command
    {
        // Close write end of pipe
        close(pipefd[1]);
        
        // Redirect stdin to pipe read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        // Execute second command
        execute_command(cmd2, cmd_info, gc);
        exit(cmd_info->exit_status);
    }
    
    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    
    // Wait for both commands to complete
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    
    // Set exit status to the status of the second command
    if (WIFEXITED(status2))
        cmd_info->exit_status = WEXITSTATUS(status2);
    else
        cmd_info->exit_status = 1;
}
