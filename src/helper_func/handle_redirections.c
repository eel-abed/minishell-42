/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:25:33 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/22 17:25:59 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_input_redirect(char **args, int i, t_command *cmd_info)
{
    if (!args[i + 1])
        return (i);
    cmd_info->input_file = args[i + 1];
    return (i + 2);
}

int	handle_output_redirect(char **args, int i, t_command *cmd_info)
{
    if (!args[i + 1])
        return (i);
    cmd_info->output_file = args[i + 1];
    cmd_info->heredoc_flag = false;
    return (i + 2);
}

int	handle_append_redirect(char **args, int i, t_command *cmd_info)
{
    if (!args[i + 1])
        return (i);
    cmd_info->output_file = args[i + 1];
    cmd_info->heredoc_flag = false;
    // Set append flag if needed in your t_command structure
    return (i + 2);
}

int	handle_heredoc(char **args, int i, t_command *cmd_info)
{
    if (!args[i + 1])
        return (i);
    cmd_info->delimiter = args[i + 1];
    cmd_info->heredoc_flag = true;
    return (i + 2);
}
