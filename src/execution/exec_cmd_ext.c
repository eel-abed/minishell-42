/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/20 19:14:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env_var	*get_path_variable(t_env *env)
{
	t_env_var	*path_var;

	path_var = env->vars;
	while (path_var)
	{
		if (ft_strncmp(path_var->key, "PATH", 4) == 0)
			break ;
		path_var = path_var->next;
	}
	return (path_var);
}

// static int	handle_child_failure(char *cmd_path, char **env_array)
// {
// 	int	i;

// 	perror("malloc");
// 	if (cmd_path)
// 		free(cmd_path);
// 	if (env_array)
// 	{
// 		i = 0;
// 		while (env_array[i])
// 			free(env_array[i++]);
// 		free(env_array);
// 	}
// 	exit(1);
// }

// static void	child_process(char **args, t_command *cmd)
// {
// 	char	*cmd_path;
// 	char	**env_array;

// 	cmd_path = find_command_path(args[0], cmd->env);
// 	if (!cmd_path)
// 	{
// 		write(2, args[0], ft_strlen(args[0]));
// 		write(2, ": command not found\n", 21);
// 		exit(127);
// 	}
// 	env_array = env_to_array(cmd->env);
// 	if (!env_array)
// 		handle_child_failure(cmd_path, NULL);
// 	if (execve(cmd_path, args, env_array) == -1)
// 	{
// 		perror(args[0]);
// 		free(cmd_path);
// 		handle_child_failure(NULL, env_array);
// 	}
// }

char	*find_command_path(char *cmd, t_env *env)
{
	t_env_var	*path_var;
	char		**paths;
	char		*full_path;
	int			i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_var = get_path_variable(env);
	if (!path_var || !path_var->value)
		return (NULL);
	paths = ft_split(path_var->value, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (!full_path)
			continue ;
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_paths(paths), full_path);
		free(full_path);
	}
	free_paths(paths);
	return (NULL);
}

// int	execute_external_command()
// {
// }
