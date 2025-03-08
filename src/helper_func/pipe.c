/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:18:41 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/08 19:48:23 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_tokens *tokens)
{
	int			count;
	t_tokens	*current;

	count = 1;
	current = tokens;
	while (current)
	{
		if (current->type == kind_pipe)
			count++;
		current = current->next;
	}
	return (count);
}

int	setup_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	child_process(t_pipe_data *data)
{
	if (data->i > 0)
		dup2(data->pipes[data->i - 1][0], STDIN_FILENO);
	if (data->i < data->pipe_count)
		dup2(data->pipes[data->i][1], STDOUT_FILENO);
	close_all_pipes(data->pipes, data->pipe_count);
	execute_command(data->current, data->cmd_info, data->gc);
	gc_free_all(data->gc);
	exit(data->cmd_info->exit_status);
}

void	wait_for_children(pid_t *pids, int cmd_count, t_command *cmd_info)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				cmd_info->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				cmd_info->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}
