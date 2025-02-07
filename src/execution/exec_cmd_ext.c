/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/07 17:58:48 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *join_path(char *path, char *cmd);

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

char *find_command_path(char *cmd, t_env *env)
{
    char *path = NULL;
    char **paths;
    char *full_path;
    int i;

    if (cmd[0] == '/' || cmd[0] == '.')
        return (ft_strdup(cmd));
    
    // Find PATH in environment
    i = 0;
    while (env->env_array[i])
    {
        if (strncmp(env->env_array[i], "PATH=", 5) == 0)
        {
            path = env->env_array[i] + 5;
            break;
        }
        i++;
    }
    
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
            continue;
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free_paths(paths);
            return (full_path);
        }
        free(full_path);
    }
    free_paths(paths);
    return (NULL);
}

int execute_external_command(char **args, t_command *cmd)
{
    pid_t pid;
    int status;

    if (!args || !args[0])
        return 1;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        char *cmd_path = find_command_path(args[0], cmd->env);
        if (!cmd_path)
        {
            write(2, args[0], ft_strlen(args[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }
        if (execve(cmd_path, args, cmd->env->env_array) == -1)
        {
            perror(args[0]);
            free(cmd_path);
            exit(126);
        }
    }
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
