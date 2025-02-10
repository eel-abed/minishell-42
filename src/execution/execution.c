/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/10 18:07:08 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5))
		return (true);
	return (false);
}

void	execute_builtin(char *cmd, char **args, t_command *cmd_info)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(args, cmd_info->env);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin(args);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin(cmd_info->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(args);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(args, cmd_info->env);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(args, cmd_info->env);
}

/* Helper function to handle redirections */
static void	handle_redirections(t_command *cmd_info)
{
	if (cmd_info->input_file)
		redirect_input(cmd_info->input_file);
	if (cmd_info->output_file && !cmd_info->heredoc_flag)
		redirect_output(cmd_info->output_file);
	if (cmd_info->heredoc_flag)
		heredoc(cmd_info->delimiter);
}

/* Helper function to parse command arguments */
static void	parse_command_args(char **args, t_command *cmd_info)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "<", 1))
			i = handle_input_redirect(args, i, cmd_info);
		else if (!ft_strncmp(args[i], ">", 1))
			i = handle_output_redirect(args, i, cmd_info);
		else if (!ft_strncmp(args[i], ">>", 2))
			i = handle_append_redirect(args, i, cmd_info);
		else if (!ft_strncmp(args[i], "<<", 2))
			i = handle_heredoc(args, i, cmd_info);
		else if (!ft_strncmp(args[i], "|", 1))
		{
			args[i] = NULL;
			cmd_info->cmd1 = args;
			cmd_info->cmd2 = &args[i + 1];
			break ;
		}
		else
			i++;
	}
}

static void	execute_pipe_commands(t_command *cmd_info)
{
	int	status;

	if (pipe(cmd_info->pipefd) == -1)
	{
		perror("pipe");
		g_exit_status = 1;
		return ;
	}
	// Execute first command
	cmd_info->pid1 = fork_and_execute_first(cmd_info);
	if (cmd_info->pid1 == -1)
	{
		close(cmd_info->pipefd[0]);
		close(cmd_info->pipefd[1]);
		g_exit_status = 1;
		return ;
	}
	// Execute second command
	cmd_info->pid2 = fork_and_execute_second(cmd_info);
	if (cmd_info->pid2 == -1)
	{
		close(cmd_info->pipefd[0]);
		close(cmd_info->pipefd[1]);
		waitpid(cmd_info->pid1, &status, 0);
		g_exit_status = 1;
		return ;
	}
	close(cmd_info->pipefd[0]);
	close(cmd_info->pipefd[1]);
	// Wait for first command but don't update global status
	waitpid(cmd_info->pid1, &status, 0);
}

void	execute_command(char **args, t_command *cmd_info)
{
	int	status;

	if (!args || !args[0])
		return ;
	// Reset redirection settings
	cmd_info->input_file = NULL;
	cmd_info->output_file = NULL;
	cmd_info->delimiter = NULL;
	cmd_info->heredoc_flag = false;
	parse_command_args(args, cmd_info);
	if (cmd_info->cmd1 && cmd_info->cmd2)
	{
		execute_pipe_commands(cmd_info);
		waitpid(cmd_info->pid2, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
	else
	{
		handle_redirections(cmd_info);
		if (is_builtin(args[0]))
			execute_builtin(args[0], args, cmd_info);
		else
			g_exit_status = execute_external_command(args, cmd_info);
	}
}
