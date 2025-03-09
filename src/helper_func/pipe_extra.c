/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:01:11 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/09 16:47:40 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tokens	*find_next_command(t_tokens *current)
{
	while (current && current->type != kind_pipe)
		current = current->next;
	if (current)
		current = current->next;
	return (current);
}


int	init_pipe_resources(t_pipe_data *data, t_tokens *tokens,
		t_command *cmd_info, t_garbage **gc)
{
	data->cmd_count = count_commands(tokens);
	data->pipe_count = data->cmd_count - 1;
	data->pipes = gc_malloc(gc, sizeof(int *) * data->pipe_count);
	data->pids = gc_malloc(gc, sizeof(pid_t) * data->cmd_count);
	data->cmd_info = cmd_info;
	data->gc = gc;
	data->i = 0;
	if (!data->pipes || !data->pids)
		return (0);
	while (data->i < data->pipe_count)
	{
		data->pipes[data->i] = gc_malloc(gc, sizeof(int) * 2);
		if (!data->pipes[data->i])
			return (0);
		data->i++;
	}
	return (setup_pipes(data->pipes, data->pipe_count));
}

void	execute_pipe_loop(t_pipe_data *data, t_tokens *tokens)
{
	data->current = tokens;
	data->i = 0;
	while (data->i < data->cmd_count && data->current)
	{
		if (data->i > 0)
			data->current = find_next_command(data->current);
		if (!data->current)
			break ;
		data->pids[data->i] = fork();
		if (data->pids[data->i] == -1)
		{
			perror("fork");
			return ;
		}
		if (data->pids[data->i] == 0)
			child_process(data);
		data->i++;
	}
}

void	execute_piped_commands(t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	t_pipe_data	data;

	if (!init_pipe_resources(&data, tokens, cmd_info, gc))
	{
		ft_putstr_fd("minishell: memory allocation error\n", 2);
		return ;
	}
	execute_pipe_loop(&data, tokens);
	close_all_pipes(data.pipes, data.pipe_count);
	wait_for_children(data.pids, data.cmd_count, cmd_info);
	// gc_free_all(gc);
}
