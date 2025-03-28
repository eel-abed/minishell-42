/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 17:30:06 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "stdio.h"

void		wait_pid_signals(void);

static int	try_command_path(char **paths, char *cmd, char **full_path,
		t_garbage **gc)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		*full_path = join_path(paths[i], cmd, gc);
		if (!*full_path)
		{
			i++;
			continue ;
		}
		if (access(*full_path, F_OK | X_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*find_command_path(char *cmd, t_env *env, t_garbage **gc)
{
	t_env_var	*path_var;
	char		*full_path;
	char		**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd, gc));
	if (!env)
		return (NULL);
	path_var = get_path_variable(env);
	if (!path_var || !path_var->value)
		return (NULL);
	paths = ft_split(path_var->value, ':', gc);
	if (!paths)
		return (NULL);
	if (try_command_path(paths, cmd, &full_path, gc))
		return (full_path);
	return (NULL);
}

static char	**prepare_command_args(t_tokens *tokens, t_garbage **gc)
{
	char	**cmd_args;
	int		i;
	char	*str;

	i = 0;
	while (tokens->value[i] != 32 && tokens->value[i] != '\0')
		i++;
	str = ft_substr(tokens->value, 0, i, gc);
	if (!str)
		return (NULL);
	if (ft_strncmp(str, "cat", 3) == 0 || ft_strncmp(str, "ls", 3) == 0)
		cmd_args = ft_split_hors_quotes(tokens->value, ' ', gc);
	else
		cmd_args = ft_split(tokens->value, ' ', gc);
	if (!cmd_args)
		return (NULL);
	cmd_args[1] = remove_outer_quotes(cmd_args[1], gc);
	return (cmd_args);
}

static int	execute_command_process(char *cmd_path, char **cmd_args,
		char **env_array)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execute_child(cmd_path, cmd_args, env_array);
	}
	wait_pid_signals();
	return (wait_for_child(pid));
}

int	execute_external_command(t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	char	*cmd_path;
	char	**env_array;
	char	**cmd_args;

	cmd_args = prepare_command_args(tokens, gc);
	if (!cmd_args)
		return (1);
	cmd_path = find_command_path(cmd_args[0], cmd_info->env, gc);
	if (!cmd_path)
		return (handle_command_not_found(cmd_args[0]));
	env_array = env_to_array(cmd_info->env, gc);
	if (!env_array)
		return (1);
	return (execute_command_process(cmd_path, cmd_args, env_array));
}
