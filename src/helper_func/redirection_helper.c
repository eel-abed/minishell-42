/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:03:02 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/02 17:05:24 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	handle_redirectionnn(char **parts, t_command *cmd_info, t_garbage **gc)
{
	int		i;
	bool	result;

	i = 0;
	while (parts[i])
	{
		result = process_redirection(parts, i, cmd_info, gc);
		if (!result)
			return (i > 0 && (ft_strcmp(parts[i - 1], ">") == 0
					|| ft_strcmp(parts[i - 1], ">>") == 0));
		i++;
	}
	return (true);
}
