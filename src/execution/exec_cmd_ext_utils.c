/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:04:52 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 14:55:56 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_paths(char **paths)
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

char	*join_path(char *path, char *cmd,t_garbage **gc)
{
	char	*temp;
	char	*full;

	temp = ft_strjoin(path, "/",gc);
	if (!temp)
		return (NULL);
	full = ft_strjoin(temp, cmd,gc);
	// printf("full : %p\n", full);
	// free(temp);
	return (full);
}
