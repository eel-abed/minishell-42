/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/26 17:27:02 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_heredoc(char **args, int i, t_command *cmd_info,t_garbage **gc)
{
	if (!args[i + 1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		cmd_info->exit_status = 2;
		return (i);
	}
	if (args[i + 1][0] == '\0')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `<<'", 2);
		cmd_info->exit_status = 2;
		return (i);
	}
	// Save the delimiter
	cmd_info->delimiter = ft_strdup(args[i + 1],gc);
	if (!cmd_info->delimiter)
	{
		ft_putendl_fd("minishell: memory allocation error", 2);
		cmd_info->exit_status = 1;
		return (i);
	}
	cmd_info->heredoc_flag = true;
	return (i + 2);
}

bool handle_redirectionnn(char **parts, t_command *cmd_info, t_garbage **gc)
{
    int i = 0;
    while (parts[i])
    {
        if (!ft_strcmp(parts[i], "<"))
        {
            if (parts[i + 1])
            {
                cmd_info->input_file = ft_strdup(parts[i + 1], gc);
                if (redirect_input(parts[i + 1]) < 0)
                {
                    cmd_info->exit_status = 1;
                    return false;
                }
            }
        }
        else if (!ft_strcmp(parts[i], ">"))
        {
            if (parts[i + 1])
            {
                cmd_info->output_file = ft_strdup(parts[i + 1],gc);
                if (redirect_output(parts[i + 1], 0) < 0)
                {
                    cmd_info->exit_status = 1;
                    return false;
                }
            }
            break;
        }
        else if (!ft_strcmp(parts[i], ">>"))
        {
            if (parts[i + 1])
            {
                cmd_info->output_file = ft_strdup(parts[i + 1],gc);
                if (redirect_output(parts[i + 1], 1) < 0)
                {
                    cmd_info->exit_status = 1;
                    return false;
                }
            }
            break;
        }
        i++;
    }
	return true;
}
