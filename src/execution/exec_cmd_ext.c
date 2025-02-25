/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 17:07:12 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env_var	*get_path_variable(t_env *env)
{
	if (!env)
		return NULL;
	
	if (!env->vars)
		return NULL;

	t_env_var *path_var = env->vars;
	while (path_var)
	{
		if (path_var->key && ft_strncmp(path_var->key, "PATH", 4) == 0)
			return path_var;
		
		path_var = path_var->next;
	}
	
	return NULL;
}

char	*find_command_path(char *cmd, t_env *env,t_garbage **gc)
{
    t_env_var *path_var;
    char *full_path;

	if (cmd[0] == '/' || cmd[0] == '.')
		return ft_strdup(cmd,gc);
	if (!env)
		return NULL;
	path_var = get_path_variable(env);
	if (!path_var)
		return NULL;
	if (!path_var->value)
		return NULL;
	char **paths = ft_split(path_var->value, ':',gc);
	if (!paths)
		return NULL;
	full_path = NULL;
	for (int i = 0; paths[i]; i++)
	{
		full_path = join_path(paths[i], cmd,gc);
		if (!full_path)
			continue;
		if (access(full_path, F_OK | X_OK) == 0)
			return full_path;
	}
	return NULL;
}

int execute_external_command(t_tokens *tokens, t_command *cmd_info,t_garbage **gc)
{
    char *cmd_path;
    char **env_array;
    char **cmd_args;
    int exit_status;
    pid_t pid;
    int status;

    // Split the token value into command and arguments
    cmd_args = ft_split(tokens->value, ' ',gc);
    if (!cmd_args)
        return (1);

    cmd_path = find_command_path(cmd_args[0], cmd_info->env,gc);
    if (!cmd_path)
    {
        write(2, cmd_args[0], ft_strlen(cmd_args[0]));
        write(2, ": command not found\n", 20);
        // free_paths(cmd_args);
        return (127);
    }

    env_array = env_to_array(cmd_info->env,gc);
    if (!env_array)
    {
        free(cmd_path);
        free_paths(cmd_args);
        return (1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(cmd_path);
        free_paths(env_array);
        free_paths(cmd_args);
        return (1);
    }

    if (pid == 0)  // Child process
    {
        execve(cmd_path, cmd_args, env_array);
        perror(cmd_args[0]);
        free(cmd_path);
        free_paths(env_array);
        free_paths(cmd_args);
        exit(126);
    }
    else  // Parent process
    {
        waitpid(pid, &status, 0);
        free(cmd_path);
        free_paths(env_array);
        free_paths(cmd_args);

        if (WIFEXITED(status))
            exit_status = WEXITSTATUS(status);
        else
            exit_status = 1;

        return (exit_status);
    }
}
