/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/07 18:44:04 by eel-abed         ###   ########.fr       */
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
    t_env_var *path_var;
    char **paths;
    char *full_path;
    int i;

    if (cmd[0] == '/' || cmd[0] == '.')
        return (ft_strdup(cmd));
    
    // Find PATH in environment
    path_var = env->vars;
    while (path_var)
    {
        if (ft_strncmp(path_var->key, "PATH", 4) == 0)
            break;
        path_var = path_var->next;
    }
    
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
        char **env_array;

        if (!cmd_path)
        {
            write(2, args[0], ft_strlen(args[0]));
            write(2, ": command not found\n", 21);
            exit(127);
        }

        env_array = env_to_array(cmd->env);
        if (!env_array)
        {
            perror("malloc");
            free(cmd_path);
            exit(1);
        }

        if (execve(cmd_path, args, env_array) == -1)
        {
            perror(args[0]);
            free(cmd_path);
            int i = 0;
            while (env_array[i])
                free(env_array[i++]);
            free(env_array);
            exit(126);
        }
    }
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
