/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/03 16:49:30 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*join_path(char *path, char *cmd)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd);
	free(temp);
	return (full);
}

char	*find_command_path(char *cmd)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			continue ;
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	free_paths(paths);
	return (NULL);
}

static int	handle_child_process(char **args)
{
	char	*cmd_path;

	cmd_path = find_command_path(args[0]);
	if (!cmd_path)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (execve(cmd_path, args, environ) == -1)
	{
		perror(args[0]);
		free(cmd_path);
		exit(126);
	}
	free(cmd_path);
	return (0);
}

int	execute_external_command(char **args)
{
	pid_t	pid;
	int		status;

	if (!args || !args[0])
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		return (handle_child_process(args));
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
