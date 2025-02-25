/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 15:14:11 by mafourni         ###   ########.fr       */
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
