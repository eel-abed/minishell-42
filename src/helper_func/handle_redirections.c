/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/24 19:36:42 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_redirect(char **args, int i, t_command *cmd_info)
{
	if (!args[i + 1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		cmd_info->exit_status = 2;
		return (i);
	}
	cmd_info->input_file = args[i + 1];
	return (i + 2);
}

int	handle_output_redirect(char **args, int i, t_command *cmd_info)
{
	if (!args[i + 1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		cmd_info->exit_status = 2;
		return (i);
	}
	cmd_info->output_file = args[i + 1];
	cmd_info->heredoc_flag = false;
	return (i + 2);
}

int	handle_append_redirect(char **args, int i, t_command *cmd_info)
{
	if (!args[i + 1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			2);
		cmd_info->exit_status = 2;
		return (i);
	}
	cmd_info->output_file = args[i + 1];
	cmd_info->heredoc_flag = false;
	return (i + 2);
}

int	handle_heredoc(char **args, int i, t_command *cmd_info)
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
	cmd_info->delimiter = ft_strdup(args[i + 1]);
	if (!cmd_info->delimiter)
	{
		ft_putendl_fd("minishell: memory allocation error", 2);
		cmd_info->exit_status = 1;
		return (i);
	}
	cmd_info->heredoc_flag = true;
	return (i + 2);
}
void handle_redirectionnn(char **parts, t_command *cmd_info)
{
    int i = 0;
    while (parts[i])
    {
        if (!ft_strcmp(parts[i], ">"))
        {
            if (parts[i + 1])
            {
                cmd_info->output_file = ft_strdup(parts[i + 1]);
                int fd = open(parts[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    perror("minishell");
                    return;
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
            break;
        }
        i++;
    }
}
