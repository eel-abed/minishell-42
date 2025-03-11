/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:04:52 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/06 15:09:03 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_path(char *path, char *cmd, t_garbage **gc)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(path, "/", gc);
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd, gc);
	return (full);
}

int	handle_command_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (127);
}

void	execute_child(char *cmd_path, char **cmd_args, char **env_array)
{
	execve(cmd_path, cmd_args, env_array);
	if (errno == EACCES)
    {
        perror(cmd_args[0]);
        exit(126);
    }
    else
    {
        perror(cmd_args[0]);
        exit(127);
    }
}
