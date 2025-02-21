/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:36:47 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/21 16:19:00 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	handle_pipe_error(t_command *cmd_info)
// {
// 	perror("pipe");
// 	cmd_info->exit_status = 1;
// }

// static void	execute_first_cmd(t_command *cmd_info)
// {
// 	cmd_info->pid1 = fork_and_execute_first(cmd_info);
// 	if (cmd_info->pid1 == -1)
// 	{
// 		close(cmd_info->pipefd[0]);
// 		close(cmd_info->pipefd[1]);
// 		cmd_info->exit_status = 1;
// 	}
// }

// static void	execute_second_cmd(t_command *cmd_info)
// {
// 	int	status;

// 	cmd_info->pid2 = fork_and_execute_second(cmd_info);
// 	if (cmd_info->pid2 == -1)
// 	{
// 		close(cmd_info->pipefd[0]);
// 		close(cmd_info->pipefd[1]);
// 		waitpid(cmd_info->pid1, &status, 0);
// 		cmd_info->exit_status = 1;
// 	}
// }

// void	execute_pipe_commands(t_command *cmd_info)
// {
// 	int	status;

// 	if (pipe(cmd_info->pipefd) == -1)
// 		return (handle_pipe_error(cmd_info));
// 	execute_first_cmd(cmd_info);
// 	if (cmd_info->pid1 == -1)
// 		return ;
// 	execute_second_cmd(cmd_info);
// 	if (cmd_info->pid2 == -1)
// 		return ;
// 	close(cmd_info->pipefd[0]);
// 	close(cmd_info->pipefd[1]);
// 	waitpid(cmd_info->pid1, &status, 0);
// }
